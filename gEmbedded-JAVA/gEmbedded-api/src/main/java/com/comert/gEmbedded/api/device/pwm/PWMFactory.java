package com.comert.gEmbedded.api.device.pwm;

public interface PWMFactory {

    PWMPin createPWMPin(PWMPinConfigurator pwmPinConfigurator);

}
