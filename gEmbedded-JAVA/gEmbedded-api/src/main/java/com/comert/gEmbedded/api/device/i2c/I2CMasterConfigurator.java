package com.comert.gEmbedded.api.device.i2c;

import com.comert.gEmbedded.api.device.Pin;

public interface I2CMasterConfigurator {

    I2CBus getBus();

    int getBusClockInHertz();

    int getSlaveWaitClockTimeout();

    Pin getSDAPin();

    Pin getSCLPin();

    int getSCLFallingEdgeClockDelay();

    int getSCLRisingEdgeClockDelay();

    void setWriteBuffer(byte[] writeBuffer);

    byte[] getWriteBuffer();

    void setReadBuffer(int[] readBuffer);

    int[] getReadBuffer();

    static I2CMasterPropertyConfigurator getBuilder() {
        return new I2CMasterConfiguratorImpl.I2CMasterPropertyConfiguratorImpl();
    }

    interface I2CMasterPropertyConfigurator {

        I2CMasterPropertyConfigurator bus(I2CBus i2CBus);

        I2CMasterPropertyConfigurator busClockInHertz(int busClockInHertz);

        I2CMasterPropertyConfigurator slaveWaitClockTimeout(int slaveWaitClockTimeout);

        I2CMasterPropertyConfigurator sdaPin(Pin sdaPin);

        I2CMasterPropertyConfigurator sclPin(Pin sclPin, int fallingEdgeClockDelay, int risingEdgeClockDelay);

        I2CMasterConfigurator build();

    }

}
