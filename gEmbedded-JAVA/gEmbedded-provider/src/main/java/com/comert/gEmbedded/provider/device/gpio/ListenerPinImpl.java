package com.comert.gEmbedded.provider.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.gpio.ListenerPinConfigurator;
import com.comert.gEmbedded.api.device.provider.ListenerPinParent;
import com.comert.gEmbedded.device.nativeinterface.ConfigurationVisitor;
import com.comert.gEmbedded.device.nativeinterface.GPIODriver;

public final class ListenerPinImpl extends ListenerPinParent {
    private final ListenerPinEventWorker listenerPinEventWorker;

    public ListenerPinImpl(ListenerPinConfigurator listenerPinConfigurator) throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(listenerPinConfigurator);
        final byte registerSelector = configurationVisitor.getListenerPinRegisterSelector(listenerPinConfigurator);
        this.listenerPinEventWorker = new ListenerPinEventWorker(registerSelector);
        this.listenerPinEventWorker.setPriority(Thread.MAX_PRIORITY);
    }

    private static final class ListenerPinEventWorker extends Thread {
        private final byte registerSelector;

        private volatile boolean running;

        private volatile boolean suspended;

        private ListenerPinEventWorker(byte registerSelector) {
            this.registerSelector = registerSelector;
        }

        @Override
        public void run() {
            while (running) {
                while (suspended) {
                    synchronized (this) {
                        try {
                            wait();
                        } catch (InterruptedException e) {
                            if (this.isInterrupted())
                                GPIODriver.releasePin(registerSelector); // Check side effects in native library
                        }
                    }
                }
                GPIODriver.pollPin(registerSelector);
            }
            GPIODriver.releasePin(registerSelector);
        }

        void startWorker() {
            running = true;
            this.start();
        }

        void suspendWorker() {
            suspended = true;
        }

        void resumeWorker() {
            suspended = false;
            synchronized (this){
                notify();
            }
        }

        void terminateWorker() {
            suspended = false;
            running = false;
            synchronized (this){
                notify();
            }
        }
    }

    @Override
    public synchronized void start() {
        if (!(listenerPinEventWorker.getState() == Thread.State.NEW))
            throw new RuntimeException("Listener is already started");
        listenerPinEventWorker.startWorker();
        boolean started = false;
        while (!started) {
            started = (listenerPinEventWorker.getState() == Thread.State.RUNNABLE);
        }
    }

    @Override
    public synchronized void suspend() {
        if ((listenerPinEventWorker.getState() == Thread.State.WAITING))
            throw new RuntimeException("listener already suspended");
        listenerPinEventWorker.suspendWorker();
        boolean suspended = false;
        while (!suspended) {
            suspended = (listenerPinEventWorker.getState() == Thread.State.WAITING);
        }
    }

    @Override
    public synchronized void resume() {
        if (!(listenerPinEventWorker.getState() == Thread.State.WAITING))
            throw new RuntimeException("listener already resumed");
        listenerPinEventWorker.resumeWorker();
        boolean resumed = false;
        while (!resumed) {
            resumed = !(listenerPinEventWorker.getState() == Thread.State.WAITING);
        }
    }

    @Override
    public synchronized void terminate() {
        if ((listenerPinEventWorker.getState() == Thread.State.TERMINATED))
            throw new RuntimeException("Listener is already terminated");
        listenerPinEventWorker.terminateWorker();
        boolean terminated = false;
        while (!terminated) {
            terminated = (listenerPinEventWorker.getState() == Thread.State.TERMINATED);
        }
    }

    @Override
    public synchronized boolean isStarted() {
        return (listenerPinEventWorker.getState() == Thread.State.RUNNABLE);
    }

    @Override
    public synchronized boolean isSuspended() {
        return (listenerPinEventWorker.getState() == Thread.State.WAITING);
    }

    @Override
    public synchronized boolean isResumed() {
        return !(listenerPinEventWorker.getState() == Thread.State.WAITING);
    }

    @Override
    public synchronized boolean isTerminated() {
        return (listenerPinEventWorker.getState() == Thread.State.TERMINATED);
    }

}
