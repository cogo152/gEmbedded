package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceIOException;

public interface OutputPin {

    void setHigh();

    void setHighWithException() throws DeviceIOException;

    void setLow();

    void setLowWithException() throws DeviceIOException;

    boolean isHigh();

    boolean isLow();

}
