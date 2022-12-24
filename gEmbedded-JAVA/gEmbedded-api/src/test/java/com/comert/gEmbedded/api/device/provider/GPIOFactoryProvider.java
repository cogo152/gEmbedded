package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.gpio.InputPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.OutputPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.ListenerPinConfigurator;
import org.junit.jupiter.api.Disabled;

@Disabled
public class GPIOFactoryProvider extends GPIOFactoryProviderParent {

    public GPIOFactoryProvider() {
    }

    @Override
    protected InputPinParent _createDigitalInputPin(InputPinConfigurator digitalInputPinConfigurator) throws DeviceConfigurationException {
        return null;
    }

    @Override
    protected ListenerPinParent _createListenerPin(ListenerPinConfigurator listenerPinConfigurator) throws DeviceConfigurationException {
        return null;
    }

    @Override
    protected OutputPinParent _createDigitalOutputPin(OutputPinConfigurator digitalOutputPinConfigurator) throws DeviceConfigurationException {
        return null;
    }


}
