package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.i2c.I2CMasterConfigurator;
import com.comert.gEmbedded.provider.device.i2c.I2CMasterImpl;

public final class I2CMasterFactoryProvider extends I2CMasterFactoryProviderParent {

    @Override
    protected I2CMasterParent _createI2Master(I2CMasterConfigurator i2cMasterConfigurator) throws DeviceConfigurationException {
        return new I2CMasterImpl(i2cMasterConfigurator);
    }

}
