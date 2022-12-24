package com.comert.gEmbedded.api.device.pwm;

import com.comert.gEmbedded.api.device.Pin;

public interface PWMPinConfigurator {

    Pin getPin();

    PWMMode getPWMMode();

    PWMPolarity getPWMPolarity();

    PWMSilence getPWMSilence();

    int getRange();

    static PWMPinPropertyConfigurator getBuilder() {
        return new PWMPinConfiguratorImpl.PWMPinPropertyConfiguratorImpl();
    }

    interface PWMPinPropertyConfigurator {

        PWMPinPropertyConfigurator pin(Pin pin);

        PWMPinPropertyConfigurator mode(PWMMode pwmMode);

        PWMPinPropertyConfigurator polarity(PWMPolarity pwmPolarity);

        PWMPinPropertyConfigurator silence(PWMSilence pwmSilence);

        PWMPinPropertyConfigurator range(int range);

        PWMPinConfigurator build();

    }

}
