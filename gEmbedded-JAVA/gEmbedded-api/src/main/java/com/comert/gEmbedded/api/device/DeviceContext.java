package com.comert.gEmbedded.api.device;

import com.comert.gEmbedded.api.device.gpio.GPIOFactory;
import com.comert.gEmbedded.api.device.i2c.I2CMasterFactory;
import com.comert.gEmbedded.api.device.pwm.PWMFactory;

public interface DeviceContext {

    /**
     * Sets the device context up.
     * @throws RuntimeException if the device is already setup or setup fails.
     */
    void setupDevice() throws RuntimeException;

    /**
     * Shuts the device context down.
     * @throws RuntimeException if the device is already shutdown or shutdown fails.
     */
    void shutdownDevice() throws RuntimeException;

    /**
     * @return GPIOFactory
     * @throws RuntimeException if the device is not setup or already shutdown.
     */
    GPIOFactory getGPIOFactoryInstance() throws RuntimeException;

    PWMFactory getPWMFactoryInstance() throws RuntimeException;

    /**
     * @return I2CMasterFactory
     * @throws RuntimeException if the device is not setup or already shutdown.
     */
    I2CMasterFactory getI2CMasterFactoryInstance() throws RuntimeException;

}
