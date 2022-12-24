package com.comert.gEmbedded.api.device.pwm;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.Pin;

import java.util.StringJoiner;

final class PWMPinConfiguratorImpl implements PWMPinConfigurator {

    private final Pin pin;

    private final PWMMode pwmMode;

    private final PWMPolarity pwmPolarity;

    private final PWMSilence pwmSilence;

    private final int range;

    @Override
    public Pin getPin() {
        return pin;
    }

    @Override
    public PWMMode getPWMMode() {
        return pwmMode;
    }

    @Override
    public PWMPolarity getPWMPolarity() {
        return pwmPolarity;
    }

    @Override
    public PWMSilence getPWMSilence() {
        return pwmSilence;
    }

    @Override
    public int getRange() {
        return range;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", PWMPinConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("pin=" + pin)
                .add("pwmMode=" + pwmMode)
                .add("pwmPolarity=" + pwmPolarity)
                .add("pwmSilence=" + pwmSilence)
                .add("range=" + range)
                .toString();
    }

    public PWMPinConfiguratorImpl(Pin pin, PWMMode pwmMode, PWMPolarity pwmPolarity, PWMSilence pwmSilence, int range) {

        if (pin == null) {
            try {
                throw new DeviceConfigurationException(PWMConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pin");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }


        if (pwmMode == null) {
            try {
                throw new DeviceConfigurationException(PWMConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pwmMode");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        if (pwmPolarity == null) {
            try {
                throw new DeviceConfigurationException(PWMConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pwmPolarity");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        if (pwmSilence == null) {
            try {
                throw new DeviceConfigurationException(PWMConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "pwmSilence");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }

        if (range < 0) {
            try {
                throw new DeviceConfigurationException(PWMConfigurationMessage.PIN_FIELD_IS_NOT_VALID, "range");
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
        }


        this.pin = pin;
        this.pwmMode = pwmMode;
        this.pwmPolarity = pwmPolarity;
        this.pwmSilence = pwmSilence;
        this.range = range;

    }

    static class PWMPinPropertyConfiguratorImpl implements PWMPinPropertyConfigurator {

        private Pin pin;

        private PWMMode pwmMode;


        private PWMPolarity pwmPolarity;


        private PWMSilence pwmSilence;

        private int range;

        PWMPinPropertyConfiguratorImpl() {
        }


        @Override
        public PWMPinPropertyConfigurator pin(Pin pin) {
            this.pin = pin;
            return this;
        }

        @Override
        public PWMPinPropertyConfigurator mode(PWMMode pwmMode) {
            this.pwmMode = pwmMode;
            return this;
        }

        @Override
        public PWMPinPropertyConfigurator polarity(PWMPolarity pwmPolarity) {
            this.pwmPolarity = pwmPolarity;
            return this;
        }

        @Override
        public PWMPinPropertyConfigurator silence(PWMSilence pwmSilence) {
            this.pwmSilence = pwmSilence;
            return this;
        }

        @Override
        public PWMPinPropertyConfigurator range(int range) {
            this.range = range;
            return this;
        }

        @Override
        public PWMPinConfigurator build() {
            return new PWMPinConfiguratorImpl(pin, pwmMode, pwmPolarity, pwmSilence, range);
        }
    }


}
