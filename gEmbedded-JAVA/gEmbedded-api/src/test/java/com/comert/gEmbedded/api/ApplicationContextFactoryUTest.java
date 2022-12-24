package com.comert.gEmbedded.api;

import com.comert.gEmbedded.api.device.DeviceContext;
import com.comert.gEmbedded.api.testutil.InstanceProducer;
import com.comert.gEmbedded.api.testutil.MultiThreadingTest;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import static org.junit.jupiter.api.Assertions.*;

@EnabledForJreRange(min = JRE.JAVA_17)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class ApplicationContextFactoryUTest {

    @Test
    public void testSuccessWhenDeviceContextInstanceIsCreated() {
        assertDoesNotThrow(ApplicationContextFactory::getDeviceContextInstance);
        assertNotNull(ApplicationContextFactory.getDeviceContextInstance());
    }

    @Test
    public void testSuccessThatInstancesAreSingleTon() {
        final var deviceContext1 = ApplicationContextFactory.getDeviceContextInstance();
        final var deviceContext2 = ApplicationContextFactory.getDeviceContextInstance();
        assertSame(deviceContext1, deviceContext2);
    }

    @Test
    public void testSuccessThatInstancesAreSingleTonWhenMultiThreadingAccess() throws InterruptedException {
        final InstanceProducer<DeviceContext> instanceProducer = ApplicationContextFactory::getDeviceContextInstance;

        final var instanceSize = MultiThreadingTest.instanceSize(instanceProducer);
        assertEquals(1, instanceSize);
    }

}