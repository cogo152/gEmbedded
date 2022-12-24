package com.comert.gEmbedded.api.device.provider;

import com.comert.gEmbedded.api.device.DeviceContext;
import com.comert.gEmbedded.api.ApplicationContextFactory;
import com.comert.gEmbedded.api.device.gpio.GPIOFactory;
import com.comert.gEmbedded.api.testutil.InstanceProducer;
import com.comert.gEmbedded.api.testutil.MultiThreadingTest;
import com.comert.gEmbedded.api.util.InstanceExceptionMessage;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.*;

@EnabledForJreRange(min = JRE.JAVA_17)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class DeviceContextProviderParentUTest {

    private DeviceContext device;

    @BeforeAll
    public void setUpTest(){
        device = ApplicationContextFactory.getDeviceContextInstance();
        device.setupDevice();
    }

    @AfterAll
    public void tearDownTest(){
        device.shutdownDevice();
    }

    @Test
    public void testFailWhenDeviceProviderIsBeingCreatedOutOfFactory() {
        final var desiredClassName = "com.comert.gEmbedded.api.ApplicationContextFactory";

        assertThatExceptionOfType(RuntimeException.class)
                .isThrownBy(
                        DeviceContextProvider::new
                )
                .withMessage(InstanceExceptionMessage.OUT_OF_DESIRED_CLASS +" : "+desiredClassName);
    }

    @Test
    public void testSuccessWhenProviderIsBeingCreatedInFactoryClass() {
        assertDoesNotThrow(
                ApplicationContextFactory::getDeviceContextInstance
        );
    }

    @Test
    public void testSuccesWhenGetGPIOFactory() {
        GPIOFactory factory = device.getGPIOFactoryInstance();
        assertNotNull(factory);
        assertEquals(GPIOFactoryProvider.class, factory.getClass());
    }

    @Test
    public void testSuccesGPIOFactorySingleTonInstance() {
        GPIOFactory factory1 = device.getGPIOFactoryInstance();
        GPIOFactory factory2 = device.getGPIOFactoryInstance();
        assertSame(factory1, factory2);
        assertEquals(factory1, factory2);
    }

    @Test
    public void testSuccesGPIOFactorySingleTonMultiThreadingAccsess() throws InterruptedException {
        InstanceProducer<GPIOFactory> gpioFactoryInstanceProcuder = device::getGPIOFactoryInstance;

        int instanceSize = MultiThreadingTest.instanceSize(gpioFactoryInstanceProcuder);
        assertEquals(1, instanceSize);
    }

}