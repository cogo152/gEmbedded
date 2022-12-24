package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.gpio.InputPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.ListenerPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.OutputPinConfigurator;
import com.comert.gEmbedded.api.device.pwm.PWMPinConfigurator;
import com.comert.gEmbedded.provider.device.gpio.InputPinImpl;
import com.comert.gEmbedded.provider.device.gpio.ListenerPinImpl;
import com.comert.gEmbedded.provider.device.gpio.OutputPinImpl;
import com.comert.gEmbedded.provider.device.pwm.PWMPinImpl;

public final class PWMFactoryProvider extends PWMFactoryProviderParent {

    @Override
    protected PWMPinParent _createPWMPin(PWMPinConfigurator pwmPinConfigurator) throws DeviceConfigurationException {
        return new PWMPinImpl(pwmPinConfigurator);
    }

}
