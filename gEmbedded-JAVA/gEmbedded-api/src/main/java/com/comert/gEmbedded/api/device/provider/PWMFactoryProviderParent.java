package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.pwm.PWMFactory;
import com.comert.gEmbedded.api.device.pwm.PWMPin;
import com.comert.gEmbedded.api.device.pwm.PWMPinConfigurator;
import com.comert.gEmbedded.api.util.InstanceCreationException;
import com.comert.gEmbedded.api.util.InstanceCreationValidator;

public abstract class PWMFactoryProviderParent implements PWMFactory {

    protected PWMFactoryProviderParent() {
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
    public final PWMPin createPWMPin(PWMPinConfigurator pwmPinConfigurator) {
        if (pwmPinConfigurator == null) {
            throw new IllegalArgumentException("pwmPinConfigurator can not be null");
        }
        try {
            return _createPWMPin(pwmPinConfigurator);
        } catch (DeviceConfigurationException deviceConfigurationException) {
            throw new RuntimeException(deviceConfigurationException.getMessage());
        }
    }


    protected abstract PWMPinParent _createPWMPin(PWMPinConfigurator pwmPinConfigurator) throws DeviceConfigurationException;


}
