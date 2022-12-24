package com.comert.gEmbedded.api.device.i2c;

public interface I2CMasterFactory {

    I2CMaster createI2CMaster(I2CMasterConfigurator I2cMasterConfigurator);

}
