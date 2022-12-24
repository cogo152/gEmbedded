package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.i2c.I2CMasterConfigurator;
import org.junit.jupiter.api.Disabled;

@Disabled
public class I2CMasterFactoryProvider extends I2CMasterFactoryProviderParent {

    public I2CMasterFactoryProvider(){}

    @Override
    protected I2CMasterParent _createI2Master(I2CMasterConfigurator I2CMasterConfigurator) {
        return null;
    }

}
