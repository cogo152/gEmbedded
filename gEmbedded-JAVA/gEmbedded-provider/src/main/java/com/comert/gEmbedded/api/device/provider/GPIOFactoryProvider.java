package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.gpio.InputPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.ListenerPinConfigurator;
import com.comert.gEmbedded.api.device.gpio.OutputPinConfigurator;
import com.comert.gEmbedded.provider.device.gpio.InputPinImpl;
import com.comert.gEmbedded.provider.device.gpio.ListenerPinImpl;
import com.comert.gEmbedded.provider.device.gpio.OutputPinImpl;

public final class GPIOFactoryProvider extends GPIOFactoryProviderParent {

    @Override
    protected InputPinParent _createInputPin(InputPinConfigurator inputPinConfigurator) throws DeviceConfigurationException {
        return new InputPinImpl(inputPinConfigurator);
    }

    @Override
    protected ListenerPinParent _createListenerPin(ListenerPinConfigurator listenerPinConfigurator) throws DeviceConfigurationException {
        return new ListenerPinImpl(listenerPinConfigurator);
    }

    @Override
    protected OutputPinParent _createOutputPin(OutputPinConfigurator outputPinConfigurator) throws DeviceConfigurationException {
        return new OutputPinImpl(outputPinConfigurator);
    }

}
