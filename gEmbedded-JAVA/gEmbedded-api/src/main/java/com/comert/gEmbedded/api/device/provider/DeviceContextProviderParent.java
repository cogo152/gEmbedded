package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.ApplicationContextFactory;
import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.DeviceContext;
import com.comert.gEmbedded.api.device.DeviceExecutionException;
import com.comert.gEmbedded.api.device.gpio.GPIOFactory;
import com.comert.gEmbedded.api.device.i2c.I2CMasterFactory;
import com.comert.gEmbedded.api.device.pwm.PWMFactory;
import com.comert.gEmbedded.api.util.InstanceCreationException;
import com.comert.gEmbedded.api.util.InstanceCreationValidator;
import com.comert.gEmbedded.api.util.ProviderException;
import com.comert.gEmbedded.api.util.ProviderFactory;

public abstract class DeviceContextProviderParent implements DeviceContext {

    private static GPIOFactoryProviderParent gpioFactoryProvider;

    private static PWMFactoryProviderParent pwmFactoryProvider;

    private static I2CMasterFactoryProviderParent i2cMasterFactoryProvider;

    private volatile boolean deviceExecuting;

    protected DeviceContextProviderParent() {
        synchronized (this) {
            final var desiredClass = ApplicationContextFactory.class;
            try {
                InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
            } catch (InstanceCreationException instanceCreationException) {
                throw new RuntimeException(instanceCreationException.getMessage());
            }
        }
    }

    @Override
    public final synchronized void setupDevice() {
        if (deviceExecuting) {
            try {
                throw new DeviceExecutionException(DeviceContextExecutionMessage.ALREADY_SETUP, getDeviceName());
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        } else {
            try {
                _setupDevice();
            } catch (DeviceConfigurationException deviceConfigurationException) {
                throw new RuntimeException(deviceConfigurationException.getMessage());
            }
            deviceExecuting = true;
        }
    }

    protected abstract void _setupDevice() throws DeviceConfigurationException;

    @Override
    public final synchronized void shutdownDevice() {
        if (deviceExecuting) {
            try {
                _shutdownDevice();
            } catch (DeviceConfigurationException deviceConfigurationException) {
                //_forceShutdownDevice();
                throw new RuntimeException(deviceConfigurationException.getMessage() + " Shutdown forced.");
                // throw new RuntimeException(deviceConfigurationException.getMessage()+" Shutdown forced.");

            }
            deviceExecuting = false;
        } else {
            try {
                throw new DeviceExecutionException(DeviceContextExecutionMessage.ALREADY_SHUTDOWN, getDeviceName());
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        }
    }


    protected abstract void _shutdownDevice() throws DeviceConfigurationException;

    //protected abstract void _forceShutdownDevice();

    protected abstract String getDeviceName();

    @Override
    public synchronized final GPIOFactory getGPIOFactoryInstance() {
        if (!deviceExecuting)
            try {
                throw new DeviceExecutionException(DeviceContextExecutionMessage.MUST_BE_SETUP, getDeviceName());
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        if (gpioFactoryProvider == null) {
            final var providerParentClass = GPIOFactoryProviderParent.class;
            try {
                gpioFactoryProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerParentClass);
            } catch (ProviderException providerException) {
                throw new RuntimeException(providerException.getMessage());
            }
        }
        return gpioFactoryProvider;
    }

    @Override
    public synchronized final PWMFactory getPWMFactoryInstance() {
        if (!deviceExecuting)
            try {
                throw new DeviceExecutionException(DeviceContextExecutionMessage.MUST_BE_SETUP, getDeviceName());
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        if (pwmFactoryProvider == null) {
            final var providerParentClass = PWMFactoryProviderParent.class;
            try {
                pwmFactoryProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerParentClass);
            } catch (ProviderException providerException) {
                throw new RuntimeException(providerException.getMessage());
            }
        }
        return pwmFactoryProvider;
    }

    @Override
    public synchronized final I2CMasterFactory getI2CMasterFactoryInstance() {
        if (!deviceExecuting)
            try {
                throw new DeviceExecutionException(DeviceContextExecutionMessage.MUST_BE_SETUP, getDeviceName());
            } catch (DeviceExecutionException deviceExecutionException) {
                throw new RuntimeException(deviceExecutionException.getMessage());
            }
        if (i2cMasterFactoryProvider == null) {
            final var providerParentClass = I2CMasterFactoryProviderParent.class;
            try {
                i2cMasterFactoryProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerParentClass);
            } catch (ProviderException providerException) {
                throw new RuntimeException(providerException.getMessage());
            }
        }
        return i2cMasterFactoryProvider;
    }

}
