package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.Pin;

import java.util.StringJoiner;

final class ListenerPinConfiguratorImpl implements ListenerPinConfigurator {

    private final Pin pin;
    private final Event eventStatus;
    private final int timeOutInMilSec;
    private final ListenerCallBack listenerCallBack;

    @Override
    public Pin getPin() {
        return pin;
    }

    @Override
    public Event getEventStatus() {
        return eventStatus;
    }

    @Override
    public int getTimeoutInMilSec() {
        return timeOutInMilSec;
    }

    @Override
    public ListenerCallBack getCallBack() {
        return listenerCallBack;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", ListenerPinConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("pin=" + pin)
                .add("eventStatus=" + eventStatus)
                .add("timeOutInMilSec=" + timeOutInMilSec)
                .add("listenerCallBack=" + listenerCallBack)
                .toString();
    }

    public ListenerPinConfiguratorImpl(Pin pin, Event eventStatus, int timeOutInMilSec, ListenerCallBack listenerCallBack) {

        if (pin == null) {
            try {
                throw new DeviceConfigurationException(GPIOConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pin");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        if (eventStatus == null) {
            try {
                throw new DeviceConfigurationException(GPIOConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "eventStatus");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        if (timeOutInMilSec < 1) {
            try {
                throw new DeviceConfigurationException(GPIOConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "timeOutInMilSec");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        if (listenerCallBack == null) {
            try {
                throw new DeviceConfigurationException(GPIOConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "listenerCallBack");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        this.pin = pin;
        this.eventStatus = eventStatus;
        this.timeOutInMilSec = timeOutInMilSec;
        this.listenerCallBack = listenerCallBack;

    }

    static class ListenerPinPropertyConfiguratorImpl implements ListenerPinPropertyConfigurator {

        private Pin pin;
        private Event eventStatus;
        private int timeoutInMilSec;
        private ListenerCallBack listenerCallBack;

        ListenerPinPropertyConfiguratorImpl() {
        }


        @Override
        public ListenerPinPropertyConfigurator pin(Pin pin) {
            this.pin = pin;
            return this;
        }

        @Override
        public ListenerPinPropertyConfigurator eventStatus(Event eventStatus) {
            this.eventStatus = eventStatus;
            return this;
        }

        @Override
        public ListenerPinPropertyConfigurator timeoutInMilSec(int timeoutInMilSec) {
            this.timeoutInMilSec = timeoutInMilSec;
            return this;
        }

        @Override
        public ListenerPinPropertyConfigurator callBack(ListenerCallBack listenerCallBack) {
            this.listenerCallBack = listenerCallBack;
            return this;
        }

        public ListenerPinConfigurator build() {
            return new ListenerPinConfiguratorImpl(pin, eventStatus, timeoutInMilSec, listenerCallBack);
        }

    }

}
