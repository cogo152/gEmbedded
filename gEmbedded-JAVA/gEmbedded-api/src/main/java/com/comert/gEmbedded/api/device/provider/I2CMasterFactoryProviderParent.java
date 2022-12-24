package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.i2c.I2CMaster;
import com.comert.gEmbedded.api.device.i2c.I2CMasterConfigurator;
import com.comert.gEmbedded.api.device.i2c.I2CMasterFactory;
import com.comert.gEmbedded.api.util.InstanceCreationException;
import com.comert.gEmbedded.api.util.InstanceCreationValidator;

public abstract class I2CMasterFactoryProviderParent implements I2CMasterFactory {

    protected I2CMasterFactoryProviderParent() {
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
    public final I2CMaster createI2CMaster(I2CMasterConfigurator i2cMasterConfigurator) {
        if (i2cMasterConfigurator == null) {
            throw new IllegalArgumentException("i2cMasterConfigurator can not be null");
        }
        try {
            return _createI2Master(i2cMasterConfigurator);
        } catch (DeviceConfigurationException deviceConfigurationException) {
            throw new RuntimeException(deviceConfigurationException.getMessage());
        }
    }

    protected abstract I2CMasterParent _createI2Master(I2CMasterConfigurator i2cMasterConfigurator) throws DeviceConfigurationException;
}
