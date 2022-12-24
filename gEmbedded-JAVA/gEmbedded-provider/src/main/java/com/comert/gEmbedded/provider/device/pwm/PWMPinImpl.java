package com.comert.gEmbedded.provider.device.pwm;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.DeviceIOException;
import com.comert.gEmbedded.api.device.provider.PWMPinParent;
import com.comert.gEmbedded.api.device.pwm.PWMPinConfigurator;
import com.comert.gEmbedded.device.nativeinterface.ConfigurationVisitor;
import com.comert.gEmbedded.device.nativeinterface.PWMDriver;

public final class PWMPinImpl extends PWMPinParent {

    private final byte registerSelector;

    private final int range;

    public PWMPinImpl(PWMPinConfigurator pwmPinConfigurator) throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(pwmPinConfigurator);
        this.registerSelector = configurationVisitor.getPWMPinRegisterSelector(pwmPinConfigurator);
        this.range = pwmPinConfigurator.getRange();
    }


    @Override
    public void enable() {
        PWMDriver.enablePWMPin(registerSelector);
    }

    @Override
    public void disable() {
        PWMDriver.disablePWMPin(registerSelector);
    }

    @Override
    public void writeData(int data) {
        PWMDriver.writePWMPinData(registerSelector, data);
    }

    @Override
    public void writeDataWithException(int data) throws DeviceIOException {
        PWMDriver.writePWMPinDataWithException(registerSelector, data);
    }

    @Override
    public void writeDutyCycle(double dutyCycle) {
        if ((dutyCycle < 0.0) || (dutyCycle > 100.0)) {
            throw new IllegalArgumentException();
        }
        final int data = (int) (dutyCycle * range / 100);
        PWMDriver.writePWMPinData(registerSelector, data);
    }

    @Override
    public void writeDutyCycleWithException(double dutyCycle) throws DeviceIOException {
        if ((dutyCycle < 0.0) || (dutyCycle > 100.0)) {
            throw new IllegalArgumentException();
        }
        final int data = (int) (dutyCycle * range / 100);
        PWMDriver.writePWMPinDataWithException(registerSelector, data);
    }

    @Override
    public void writeVoltage(double voltage) {
        if ((voltage < 0.0) || (voltage > 3.3)) {
            throw new IllegalArgumentException();
        }
        final int data = (int) (voltage * range / 3.3);
        PWMDriver.writePWMPinData(registerSelector, data);
    }

    @Override
    public void writeVoltageWithException(double voltage) throws DeviceIOException {
        if ((voltage < 0.0) || (voltage > 3.3)) {
            throw new IllegalArgumentException();
        }
        final int data = (int) (voltage * range / 3.3);
        PWMDriver.writePWMPinDataWithException(registerSelector, data);
    }

}
