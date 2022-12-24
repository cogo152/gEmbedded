package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.ApplicationContextFactory;
import com.comert.gEmbedded.api.device.DeviceContext;
import com.comert.gEmbedded.api.device.gpio.GPIOFactory;
import com.comert.gEmbedded.api.device.i2c.I2CMasterFactory;
import com.comert.gEmbedded.api.device.provider.DeviceContextExecutionMessage;

import org.junit.jupiter.api.*;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertNotNull;

@EnabledForJreRange(min = JRE.JAVA_17)
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class DeviceContextUTest {

    private DeviceContext deviceContext;
    private final String deviceName = " : Raspberrypi-4B";

    @Order(1)
    @Test
    public void testSuccessWhenDeviceContextInstanceIsCreated() {
        deviceContext = ApplicationContextFactory.getDeviceContextInstance();
        assertNotNull(deviceContext);
    }

    @Order(2)
    @Test
    public void testSuccessWhenDeviceIsSetup() {
        assertDoesNotThrow(() -> deviceContext.setupDevice());
    }

    @Order(3)
    @Test
    public void testSuccessWhenGPIOFactoryIsCreated() {
        GPIOFactory factory = deviceContext.getGPIOFactoryInstance();
        assertNotNull(factory);
    }

    @Order(4)
    @Test
    public void testSuccessWhenI2CMasterFactoryIsCreated() {
        I2CMasterFactory factory = deviceContext.getI2CMasterFactoryInstance();
        assertNotNull(factory);
    }

    @Order(5)
    @Test
    public void testSuccessWhenDeviceIsShutdown() {
        assertDoesNotThrow(() -> deviceContext.shutdownDevice());
    }

    @Order(6)
    @Test
    public void testFailWhenDeviceIsAlreadySetup() {
        deviceContext.setupDevice();
        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> deviceContext.setupDevice()
                )
                .withMessage(
                        DeviceContextExecutionMessage.ALREADY_SETUP + deviceName
                );
    }

    @Order(7)
    @Test
    public void testFailWhenDeviceIsAlreadyShutdown() {
        deviceContext.shutdownDevice();
        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> deviceContext.shutdownDevice()
                )
                .withMessage(
                		DeviceContextExecutionMessage.ALREADY_SHUTDOWN + deviceName
                );
    }

    @Order(8)
    @Test
    public void testFailWhenGPIOFactoryIsCreatedBeforeDeviceSetup() {
        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> deviceContext.getGPIOFactoryInstance()
                )
                .withMessage(
                		DeviceContextExecutionMessage.MUST_BE_SETUP + deviceName
                );
        deviceContext.setupDevice();
    }

    @Order(9)
    @Test
    public void testFailWhenGPIOFactoryIsCreatedAfterDeviceShutdown() {
        deviceContext.shutdownDevice();
        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> deviceContext.getGPIOFactoryInstance()
                )
                .withMessage(
                		DeviceContextExecutionMessage.MUST_BE_SETUP + deviceName
                );
    }

    @Order(10)
    @Test
    public void testFailWhenWhenI2CMasterFactoryIsCreatedBeforeDeviceSetup() {
        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> deviceContext.getI2CMasterFactoryInstance()
                )
                .withMessage(
                		DeviceContextExecutionMessage.MUST_BE_SETUP + deviceName
                );
        deviceContext.setupDevice();
    }

    @Order(11)
    @Test
    public void testFailWhenI2CMasterFactoryIsCreatedAfterDeviceShutdown() {
        deviceContext.shutdownDevice();
        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        () -> deviceContext.getI2CMasterFactoryInstance()
                )
                .withMessage(
                		DeviceContextExecutionMessage.MUST_BE_SETUP + deviceName
                );
    }

}