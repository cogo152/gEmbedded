package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.Pin;

import java.util.StringJoiner;

final class OutputPinConfiguratorImpl implements OutputPinConfigurator {

    private final Pin pin;

    @Override
    public Pin getPin() {
        return pin;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", OutputPinConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("pin=" + pin)
                .toString();
    }

    public OutputPinConfiguratorImpl(Pin pin) {

        if (pin == null) {
            try {
                throw new DeviceConfigurationException(GPIOConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pin");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        this.pin = pin;
    }

    static class OutputPinPropertyConfiguratorImpl implements OutputPinPropertyConfigurator {

        private Pin pin;

        OutputPinPropertyConfiguratorImpl() {
        }

        @Override
        public OutputPinPropertyConfigurator pin(Pin pin) {
            this.pin = pin;
            return this;
        }

        public OutputPinConfigurator build() {
            return new OutputPinConfiguratorImpl(pin);
        }

    }

}
