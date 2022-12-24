package com.comert.gEmbedded.api.device.gpio;

public interface GPIOFactory {

    InputPin createInputPin(InputPinConfigurator inputPinConfigurator);

    ListenerPin createListenerPin(ListenerPinConfigurator listenerPinConfigurator);

    OutputPin createOutputPin(OutputPinConfigurator outputPinConfigurator);

}
