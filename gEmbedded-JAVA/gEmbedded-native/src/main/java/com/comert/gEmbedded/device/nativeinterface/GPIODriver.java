package com.comert.gEmbedded.device.nativeinterface;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.DeviceIOException;
import com.comert.gEmbedded.api.device.Pin;
import com.comert.gEmbedded.api.device.gpio.Event;
import com.comert.gEmbedded.api.device.gpio.ListenerCallBack;
import com.comert.gEmbedded.api.device.gpio.PullUpDown;

public abstract class GPIODriver {

    private GPIODriver() {
    }

    static native void setupGPIODriver() throws DeviceConfigurationException;

    static native void shutdownGPIODriver() throws DeviceConfigurationException;

    static native void configureInputPin(Pin pin, PullUpDown pullUpDown) throws DeviceConfigurationException;

    static native byte getInputPinRegisterSelector(byte pin);

    static native int getInputPinBitField(byte pin);

    static native void configureListenerPin(Pin pin, Event event, int timeoutInMilSec, ListenerCallBack listenerCallBack) throws DeviceConfigurationException;

    static native byte getListenerPinRegisterSelector(byte pin);

    static native void configureOutputPin(Pin pin) throws DeviceConfigurationException;

    static native byte getOutputPinRegisterSelector(byte pin);

    static native int getOutputPinBitField(byte pin);

    public static native boolean isPinHigh(byte registerSelector, int bitField);

    public static native boolean isPinLow(byte registerSelector, int bitField);

    public static native void setPinHigh(byte registerSelector, int bitField);

    public static native void setPinHighWithException(byte registerSelector, int bitField) throws DeviceIOException;

    public static native void setPinLow(byte registerSelector, int bitField);

    public static native void setPinLowWithException(byte registerSelector, int bitField) throws DeviceIOException;

    public static native void pollPin(byte registerSelector);

    public static native void releasePin(byte registerSelector);

}
