package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.pwm.PWMPin;
import com.comert.gEmbedded.api.util.InstanceCreationException;
import com.comert.gEmbedded.api.util.InstanceCreationValidator;

public abstract class PWMPinParent implements PWMPin {

    protected PWMPinParent() {
        synchronized (this) {
            final var desiredClass = PWMFactoryProviderParent.class;
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }

    }

}
