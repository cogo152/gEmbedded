package com.comert.gEmbedded.api.device.i2c;

import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.Pin;

import java.util.StringJoiner;

final class I2CMasterConfiguratorImpl implements I2CMasterConfigurator {

    private final I2CBus i2CBus;
    private final int busClockInHertz;
    private final int slaveWaitClockTimeout;
    private final Pin sdaPin;
    private final Pin sclPin;
    private final int sclFallingEdgeClockDelay;
    private final int sclRisingEdgeClockDelay;

    private byte[] writeBuffer;

    private int[] readBuffer;

    @Override
    public I2CBus getBus() {
        return i2CBus;
    }

    @Override
    public int getBusClockInHertz() {
        return busClockInHertz;
    }

    @Override
    public int getSlaveWaitClockTimeout() {
        return slaveWaitClockTimeout;
    }

    @Override
    public Pin getSDAPin() {
        return sdaPin;
    }

    @Override
    public Pin getSCLPin() {
        return sclPin;
    }

    @Override
    public int getSCLFallingEdgeClockDelay() {
        return sclFallingEdgeClockDelay;
    }

    @Override
    public int getSCLRisingEdgeClockDelay() {
        return sclRisingEdgeClockDelay;
    }

    @Override
    public void setWriteBuffer(byte[] writeBuffer) {
        this.writeBuffer = writeBuffer;
    }

    @Override
    public byte[] getWriteBuffer() {
        return writeBuffer;
    }

    @Override
    public void setReadBuffer(int[] readBuffer) {
        this.readBuffer = readBuffer;
    }

    @Override
    public int[] getReadBuffer() {
        return readBuffer;
    }

    @Override
    public String toString() {
        return new StringJoiner(", ", I2CMasterConfiguratorImpl.class.getSimpleName() + "[", "]")
                .add("i2CBus=" + i2CBus)
                .add("busClockInHertz=" + busClockInHertz)
                .add("slaveWaitClockTimeout=" + slaveWaitClockTimeout)
                .add("sdaPin=" + sdaPin)
                .add("sclPin=" + sclPin)
                .add("sclFallingEdgeClockDelay=" + sclFallingEdgeClockDelay)
                .add("sclRisingEdgeClockDelay=" + sclRisingEdgeClockDelay)
                .toString();
    }

    public I2CMasterConfiguratorImpl(I2CBus i2CBus,
                                     int busClockInHertz,
                                     int slaveWaitClockTimeout,
                                     Pin sdaPin,
                                     Pin sclPin,
                                     int sclFallingEdgeClockDelay,
                                     int sclRisingEdgeClockDelay) {
        // refactor
        if (i2CBus == null) {
            try {
                throw new DeviceConfigurationException(I2CBusConfigurationMessage.I2C_BUS_FIELD_IS_NOT_VALID, "i2CBus");
            } catch (DeviceConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (busClockInHertz < 0) {
            try {
                throw new DeviceConfigurationException(I2CBusConfigurationMessage.I2C_BUS_FIELD_IS_NOT_VALID, "busClockHertz<0");
            } catch (DeviceConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (slaveWaitClockTimeout < 0) {
            try {
                throw new DeviceConfigurationException(I2CBusConfigurationMessage.I2C_BUS_FIELD_IS_NOT_VALID, "busClockStretchTimout<0");
            } catch (DeviceConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sdaPin == null) {
            try {
                throw new DeviceConfigurationException(I2CBusConfigurationMessage.I2C_BUS_FIELD_IS_NOT_VALID, "sdaPin");
            } catch (DeviceConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sclPin == null) {
            try {
                throw new DeviceConfigurationException(I2CBusConfigurationMessage.I2C_BUS_FIELD_IS_NOT_VALID, "sclPin");
            } catch (DeviceConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sclFallingEdgeClockDelay < 0) {
            try {
                throw new DeviceConfigurationException(I2CBusConfigurationMessage.I2C_BUS_FIELD_IS_NOT_VALID, "sclFallingEdgeClockDelay");
            } catch (DeviceConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        if (sclRisingEdgeClockDelay < 0) {
            try {
                throw new DeviceConfigurationException(I2CBusConfigurationMessage.I2C_BUS_FIELD_IS_NOT_VALID, "sclRisingEdgeClockDelay");
            } catch (DeviceConfigurationException i2CMasterConfigurationException) {
                throw new RuntimeException(i2CMasterConfigurationException.getMessage());
            }
        }

        this.i2CBus = i2CBus;
        this.busClockInHertz = busClockInHertz;
        this.slaveWaitClockTimeout = slaveWaitClockTimeout;
        this.sdaPin = sdaPin;
        this.sclPin = sclPin;
        this.sclFallingEdgeClockDelay = sclFallingEdgeClockDelay;
        this.sclRisingEdgeClockDelay = sclRisingEdgeClockDelay;
    }


    static class I2CMasterPropertyConfiguratorImpl implements I2CMasterPropertyConfigurator {

        private I2CBus i2CBus;
        private int busClockInHertz;
        private int slaveWaitClockTimeout;
        private Pin sdaPin;
        private Pin sclPin;
        private int sclFallingEdgeClockDelay;

        private int sclRisingEdgeClockDelay;

        I2CMasterPropertyConfiguratorImpl() {
        }

        @Override
        public I2CMasterPropertyConfigurator bus(I2CBus i2CBus) {
            this.i2CBus = i2CBus;
            return this;
        }

        @Override
        public I2CMasterPropertyConfigurator busClockInHertz(int busClockInHertz) {
            this.busClockInHertz = busClockInHertz;
            return this;
        }

        @Override
        public I2CMasterPropertyConfigurator slaveWaitClockTimeout(int slaveWaitClockTimeout) {
            this.slaveWaitClockTimeout = slaveWaitClockTimeout;
            return this;
        }

        @Override
        public I2CMasterPropertyConfigurator sdaPin(Pin sdaPin) {
            this.sdaPin = sdaPin;
            return this;
        }

        @Override
        public I2CMasterPropertyConfigurator sclPin(Pin sclPin, int fallingEdgeClockDelay, int risingEdgeClockDelay) {
            this.sclPin = sclPin;
            this.sclFallingEdgeClockDelay = fallingEdgeClockDelay;
            this.sclRisingEdgeClockDelay = risingEdgeClockDelay;
            return this;
        }


        @Override
        public I2CMasterConfigurator build() {
            return new I2CMasterConfiguratorImpl(
                    i2CBus,
                    busClockInHertz,
                    slaveWaitClockTimeout,
                    sdaPin,
                    sclPin,
                    sclFallingEdgeClockDelay,
                    sclRisingEdgeClockDelay
            );
        }
    }

}


