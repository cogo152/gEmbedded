package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.gpio.*;
import com.comert.gEmbedded.api.util.InstanceCreationException;
import com.comert.gEmbedded.api.util.InstanceCreationValidator;

public abstract class GPIOFactoryProviderParent implements GPIOFactory {

    protected GPIOFactoryProviderParent() {
        synchronized (this) {
            final var desiredClass = DeviceContextProviderParent.class;
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }
    }


    @Override
    public final InputPin createInputPin(InputPinConfigurator inputPinConfigurator) {
        if (inputPinConfigurator == null) {
            throw new IllegalArgumentException("inputPinConfigurator can not be null");
        }
        try {
            return _createInputPin(inputPinConfigurator);
        } catch (DeviceConfigurationException deviceConfigurationException) {
            throw new RuntimeException(deviceConfigurationException.getMessage());
        }
    }


    protected abstract InputPinParent _createInputPin(InputPinConfigurator inputPinConfigurator) throws DeviceConfigurationException;

    @Override
    public final ListenerPin createListenerPin(ListenerPinConfigurator listenerPinConfigurator) {
        if (listenerPinConfigurator == null) {
            throw new IllegalArgumentException("listenerPinConfigurator can not be null");
        }
        try {
            return _createListenerPin(listenerPinConfigurator);
        } catch (DeviceConfigurationException deviceConfigurationException) {
            throw new RuntimeException(deviceConfigurationException.getMessage());
        }
    }

    protected abstract ListenerPinParent _createListenerPin(ListenerPinConfigurator listenerPinConfigurator) throws DeviceConfigurationException;

    @Override
    public final OutputPin createOutputPin(OutputPinConfigurator outputPinConfigurator) {
        if (outputPinConfigurator == null) {
            throw new IllegalArgumentException("outputPinConfigurator can not be null");
        }
        try {
            return _createOutputPin(outputPinConfigurator);
        } catch (DeviceConfigurationException deviceConfigurationException) {
            throw new RuntimeException(deviceConfigurationException.getMessage());
        }
    }

    protected abstract OutputPinParent _createOutputPin(OutputPinConfigurator outputPinConfigurator) throws DeviceConfigurationException;

}
