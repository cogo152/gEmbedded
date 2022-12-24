package com.comert.gEmbedded.api.device.pwm;

import com.comert.gEmbedded.api.device.DeviceIOException;

public interface PWMPin {

    void enable();

    void disable();

    void writeData(int data);

    void writeDataWithException(int data) throws DeviceIOException;

    void writeDutyCycle(double dutyCycle);

    void writeDutyCycleWithException(double dutyCycle) throws DeviceIOException;

    void writeVoltage(double voltage);

    void writeVoltageWithException(double voltage) throws DeviceIOException;

}
