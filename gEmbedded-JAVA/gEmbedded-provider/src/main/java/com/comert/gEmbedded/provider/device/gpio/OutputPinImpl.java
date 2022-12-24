package com.comert.gEmbedded.provider.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.DeviceIOException;
import com.comert.gEmbedded.api.device.gpio.OutputPinConfigurator;
import com.comert.gEmbedded.api.device.provider.OutputPinParent;
import com.comert.gEmbedded.device.nativeinterface.GPIODriver;
import com.comert.gEmbedded.device.nativeinterface.ConfigurationVisitor;

public final class OutputPinImpl extends OutputPinParent {

    private final byte registerSelector;
    private final int bitField;

    public OutputPinImpl(OutputPinConfigurator outputPinConfigurator) throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(outputPinConfigurator);
        this.registerSelector = configurationVisitor.getOutputPinRegisterSelector(outputPinConfigurator);
        this.bitField = configurationVisitor.getOutputPinBitField(outputPinConfigurator);
    }

    @Override
    public void setHigh() {
        GPIODriver.setPinHigh(registerSelector, bitField);
    }

    @Override
    public void setHighWithException() throws DeviceIOException {
        GPIODriver.setPinHighWithException(registerSelector, bitField);
    }

    @Override
    public void setLow() {
        GPIODriver.setPinLow(registerSelector, bitField);
    }

    @Override
    public void setLowWithException() throws DeviceIOException {
        GPIODriver.setPinLowWithException(registerSelector, bitField);
    }

    @Override
    public boolean isHigh() {
        return GPIODriver.isPinHigh(registerSelector, bitField);
    }

    @Override
    public boolean isLow() {
        return GPIODriver.isPinLow(registerSelector, bitField);
    }

}
