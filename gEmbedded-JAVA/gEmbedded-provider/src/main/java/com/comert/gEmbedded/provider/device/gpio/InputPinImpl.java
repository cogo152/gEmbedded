package com.comert.gEmbedded.provider.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.gpio.InputPinConfigurator;
import com.comert.gEmbedded.api.device.provider.InputPinParent;
import com.comert.gEmbedded.device.nativeinterface.GPIODriver;
import com.comert.gEmbedded.device.nativeinterface.ConfigurationVisitor;

public final class InputPinImpl extends InputPinParent {

    private final byte registerSelector;
    private final int bitField;

    public InputPinImpl(InputPinConfigurator inputPinConfigurator) throws DeviceConfigurationException {
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(inputPinConfigurator);
        this.registerSelector = configurationVisitor.getInputPinRegisterSelector(inputPinConfigurator);
        this.bitField = configurationVisitor.getInputPinBitField(inputPinConfigurator);
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
