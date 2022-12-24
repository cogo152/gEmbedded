package com.comert.gEmbedded.device.nativeinterface;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.Pin;
import com.comert.gEmbedded.api.device.gpio.*;
import com.comert.gEmbedded.api.device.i2c.I2CBus;
import com.comert.gEmbedded.api.device.i2c.I2CMasterConfigurator;
import com.comert.gEmbedded.api.device.pwm.PWMPinConfigurator;

import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public final class ConfigurationVisitor {

    private static final ConfigurationVisitor INSTANCE;

    private final Set<Pin> configuredPins;

    private final Set<I2CBus> configuredI2CBuses;

    static {

        System.loadLibrary("gEbcm271132");

        /*
       
        try {
            NativeUtils.loadLibraryFromJar("/libgEbcm271132.so");
        } catch (IOException e) {
            throw new RuntimeException("Native library could not be loaded");
        }

         */

        INSTANCE = new ConfigurationVisitor();
    }

    private ConfigurationVisitor() {
        configuredPins = new HashSet<>();
        configuredI2CBuses = new HashSet<>();
    }

    public static ConfigurationVisitor getInstance() {
        return INSTANCE;
    }

    // Device
    public synchronized void setupDevice() throws DeviceConfigurationException {
        JNIUtil.setupJNIUtil();
        DeviceDriver.setupDeviceDriver();
        GPIODriver.setupGPIODriver();
        PWMDriver.setupPWMMDriver();
        I2CMasterDriver.setupI2CMasterDriver();
    }

    public synchronized void shutdownDevice() throws DeviceConfigurationException {
        I2CMasterDriver.shutdownI2CMasterDriver();
        PWMDriver.shutdownPWMDriver();
        GPIODriver.shutdownGPIODriver();
        DeviceDriver.shutdownDeviceDriver();
        JNIUtil.shutdownJNIUtil();
    }

    private void checkIfPinIsAlreadyConfigured(final Pin pin) throws DeviceConfigurationException {
        if (configuredPins.contains(pin)) {
            throw new DeviceConfigurationException(ConfigurationMessage.PIN_IS_ALREADY_CONFIGURED, pin.getText());
        }
    }

    private void checkIfI2CBusIsAlreadyConfigured(final I2CBus i2cBus) throws DeviceConfigurationException {
        if (configuredI2CBuses.contains(i2cBus)) {
            throw new DeviceConfigurationException(ConfigurationMessage.I2C_BUS_IS_ALREADY_CONFIGURED, i2cBus.getText());
        }
    }

    private void checkIfPinIsNotYetConfigured(final Pin pin) {
        if (!configuredPins.contains(pin)) {
            throw new RuntimeException("XXXPinXXX");
        }
    }

    private void checkIfI2CBusIsNotYetConfigured(final I2CBus i2cBus) {
        if (!configuredI2CBuses.contains(i2cBus)) {
            throw new RuntimeException("BBBBusBBB");
        }
    }

    // Input Pin
    public synchronized void accept(InputPinConfigurator inputPinConfigurator) throws DeviceConfigurationException {
        checkIfPinIsAlreadyConfigured(inputPinConfigurator.getPin());

        GPIODriver.configureInputPin(inputPinConfigurator.getPin(), inputPinConfigurator.getPullUpDown());

        configuredPins.add(inputPinConfigurator.getPin());
    }

    public synchronized byte getInputPinRegisterSelector(InputPinConfigurator inputPinConfigurator) {
        checkIfPinIsNotYetConfigured(inputPinConfigurator.getPin());
        return GPIODriver.getInputPinRegisterSelector(inputPinConfigurator.getPin().getDigit());
    }

    public synchronized int getInputPinBitField(InputPinConfigurator inputPinConfigurator) {
        checkIfPinIsNotYetConfigured(inputPinConfigurator.getPin());
        return GPIODriver.getInputPinBitField(inputPinConfigurator.getPin().getDigit());
    }

    // Listener Pin
    public synchronized void accept(ListenerPinConfigurator listenerPinConfigurator) throws DeviceConfigurationException {
        checkIfPinIsAlreadyConfigured(listenerPinConfigurator.getPin());

        GPIODriver.configureListenerPin(listenerPinConfigurator.getPin(),
                listenerPinConfigurator.getEventStatus(),
                listenerPinConfigurator.getTimeoutInMilSec(),
                listenerPinConfigurator.getCallBack()
        );

        configuredPins.add(listenerPinConfigurator.getPin());
    }

    public synchronized byte getListenerPinRegisterSelector(ListenerPinConfigurator listenerPinConfigurator) {
        checkIfPinIsNotYetConfigured(listenerPinConfigurator.getPin());
        return GPIODriver.getListenerPinRegisterSelector(listenerPinConfigurator.getPin().getDigit());
    }

    // Output Pin
    public synchronized void accept(OutputPinConfigurator outputPinConfigurator) throws DeviceConfigurationException {
        checkIfPinIsAlreadyConfigured(outputPinConfigurator.getPin());

        GPIODriver.configureOutputPin(outputPinConfigurator.getPin());

        configuredPins.add(outputPinConfigurator.getPin());
    }

    public synchronized byte getOutputPinRegisterSelector(OutputPinConfigurator outputPinConfigurator) {
        checkIfPinIsNotYetConfigured(outputPinConfigurator.getPin());
        return GPIODriver.getOutputPinRegisterSelector(outputPinConfigurator.getPin().getDigit());
    }

    public synchronized int getOutputPinBitField(OutputPinConfigurator outputPinConfigurator) {
        checkIfPinIsNotYetConfigured(outputPinConfigurator.getPin());
        return GPIODriver.getOutputPinBitField(outputPinConfigurator.getPin().getDigit());
    }

    // PWM Pin
    public synchronized void accept(PWMPinConfigurator pwmPinConfigurator) throws DeviceConfigurationException {
        checkIfPinIsAlreadyConfigured(pwmPinConfigurator.getPin());

        PWMDriver.configurePWMPin(
                pwmPinConfigurator.getPin(),
                pwmPinConfigurator.getPWMMode(),
                pwmPinConfigurator.getPWMPolarity(),
                pwmPinConfigurator.getPWMSilence(),
                pwmPinConfigurator.getRange()
        );

        configuredPins.add(pwmPinConfigurator.getPin());
    }

    public synchronized byte getPWMPinRegisterSelector(PWMPinConfigurator pwmPinConfigurator) {
        checkIfPinIsNotYetConfigured(pwmPinConfigurator.getPin());
        return PWMDriver.getPWMPinRegisterSelector(pwmPinConfigurator.getPin().getDigit());
    }

    // I2C Master
    public synchronized void accept(I2CMasterConfigurator i2CMasterConfigurator) throws DeviceConfigurationException {
        checkIfI2CBusIsAlreadyConfigured(i2CMasterConfigurator.getBus());
        checkIfPinIsAlreadyConfigured(i2CMasterConfigurator.getSDAPin());
        checkIfPinIsAlreadyConfigured(i2CMasterConfigurator.getSCLPin());

        I2CMasterDriver.configureMaster(
                i2CMasterConfigurator.getBus(),
                i2CMasterConfigurator.getBusClockInHertz(),
                i2CMasterConfigurator.getSlaveWaitClockTimeout(),
                i2CMasterConfigurator.getSDAPin(),
                i2CMasterConfigurator.getSCLPin(),
                i2CMasterConfigurator.getSCLFallingEdgeClockDelay(),
                i2CMasterConfigurator.getSCLRisingEdgeClockDelay(),
                i2CMasterConfigurator.getWriteBuffer(),
                i2CMasterConfigurator.getReadBuffer()
        );

        configuredI2CBuses.add(i2CMasterConfigurator.getBus());
        configuredPins.add(i2CMasterConfigurator.getSDAPin());
        configuredPins.add(i2CMasterConfigurator.getSCLPin());
    }

    public synchronized byte getI2CBusRegisterSelector(I2CMasterConfigurator i2CMasterConfigurator) {
        checkIfI2CBusIsNotYetConfigured(i2CMasterConfigurator.getBus());
        return I2CMasterDriver.getI2CBusRegisterSelector(i2CMasterConfigurator.getBus().getDigit());
    }

}
