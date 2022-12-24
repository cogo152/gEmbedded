package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.Pin;

public interface OutputPinConfigurator {

    Pin getPin();

    static OutputPinPropertyConfigurator getBuilder() {
        return new OutputPinConfiguratorImpl.OutputPinPropertyConfiguratorImpl();
    }

    interface OutputPinPropertyConfigurator {

        OutputPinPropertyConfigurator pin(Pin pin);

        OutputPinConfigurator build();

    }

}
