package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.Pin;

import java.util.StringJoiner;

final class InputPinConfiguratorImpl implements InputPinConfigurator {

    private final Pin pin;

    private final PullUpDown pullUpDown;

    @Override
    public Pin getPin() {
        return pin;
    }

    @Override
    public PullUpDown getPullUpDown() {
        return pullUpDown;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", InputPinConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("pin=" + pin)
                .add("pullUpDown=" + pullUpDown)
                .toString();
    }

    public InputPinConfiguratorImpl(Pin pin, PullUpDown pullUpDown) {

        if (pin == null) {
            try {
                throw new DeviceConfigurationException(GPIOConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pin");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        if (pullUpDown == null) {
            try {
                throw new DeviceConfigurationException(GPIOConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pullUpDown");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        this.pin = pin;
        this.pullUpDown = pullUpDown;

    }

    static class InputPinPropertyConfiguratorImpl implements InputPinPropertyConfigurator {

        private Pin pin;
        private PullUpDown pullUpDown;

        InputPinPropertyConfiguratorImpl() {
        }

        @Override
        public InputPinPropertyConfigurator pin(Pin pin) {
            this.pin = pin;
            return this;
        }

        @Override
        public InputPinPropertyConfigurator pullUpDown(PullUpDown pullUpDown) {
            this.pullUpDown = pullUpDown;
            return this;
        }

        public InputPinConfigurator build() {
            return new InputPinConfiguratorImpl(pin, pullUpDown);
        }

    }

}
