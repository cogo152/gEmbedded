package com.comert.gEmbedded.provider.device.i2c;


import com.comert.gEmbedded.api.device.DeviceConfigurationException;
import com.comert.gEmbedded.api.device.DeviceIOException;
import com.comert.gEmbedded.api.device.i2c.I2CMasterConfigurator;
import com.comert.gEmbedded.api.device.provider.I2CMasterParent;
import com.comert.gEmbedded.device.nativeinterface.ConfigurationVisitor;
import com.comert.gEmbedded.device.nativeinterface.I2CMasterDriver;

public class I2CMasterImpl extends I2CMasterParent {


    private final byte[] writeBuffer;

    private final int[] readBuffer;

    private final byte registerSelector;

    public I2CMasterImpl(I2CMasterConfigurator i2cMasterConfigurator) throws DeviceConfigurationException {
        writeBuffer = new byte[16];
        readBuffer = new int[16];
        i2cMasterConfigurator.setReadBuffer(readBuffer);
        i2cMasterConfigurator.setWriteBuffer(writeBuffer);
        ConfigurationVisitor configurationVisitor = ConfigurationVisitor.getInstance();
        configurationVisitor.accept(i2cMasterConfigurator);
        this.registerSelector = configurationVisitor.getI2CBusRegisterSelector(i2cMasterConfigurator);
    }


    @Override
    public synchronized void writeSlave(byte slaveAddress, byte dataToSend) {
        writeBuffer[0] = dataToSend;
        I2CMasterDriver.sendData(registerSelector, slaveAddress, 1);
    }

    @Override
    public synchronized void writeSlaveWithException(byte slaveAddress, byte dataToSend) throws DeviceIOException {
        writeBuffer[0] = dataToSend;
        I2CMasterDriver.sendDataWithException(registerSelector, slaveAddress, 1);
    }

    @Override
    public synchronized int readSlave(byte slaveAddress) {
        I2CMasterDriver.receiveData(registerSelector, slaveAddress, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized int readSlaveWithException(byte slaveAddress) throws DeviceIOException {
        I2CMasterDriver.receiveDataWithException(registerSelector, slaveAddress, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized int writeAndReadSlave(byte slaveAddress, byte dataToSend) {
        writeBuffer[0] = dataToSend;
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, 1, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized int writeAndReadSlaveWithException(byte slaveAddress, byte dataToSend) throws DeviceIOException {
        writeBuffer[0] = dataToSend;
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, 1, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized void writeRegister(byte slaveAddress, byte registerAddress, byte dataToSend) {
        writeBuffer[0] = registerAddress;
        writeBuffer[1] = dataToSend;
        I2CMasterDriver.sendData(registerSelector, slaveAddress, 2);
    }

    @Override
    public synchronized void writeRegisterWithException(byte slaveAddress, byte registerAddress, byte dataToSend) throws DeviceIOException {
        writeBuffer[0] = registerAddress;
        writeBuffer[1] = dataToSend;
        I2CMasterDriver.sendDataWithException(registerSelector, slaveAddress, 2);
    }

    @Override
    public synchronized int readRegister(byte slaveAddress, byte registerAddress) {
        writeBuffer[0] = registerAddress;
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, 1, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized int readRegisterWithException(byte slaveAddress, byte registerAddress) throws DeviceIOException {
        writeBuffer[0] = registerAddress;
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, 1, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized int writeAndReadRegister(byte slaveAddress, byte registerAddress, byte dataToSend) {
        writeBuffer[0] = registerAddress;
        writeBuffer[1] = dataToSend;
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, 2, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized int writeAndReadRegisterWithException(byte slaveAddress, byte registerAddress, byte dataToSend) throws DeviceIOException {
        writeBuffer[0] = registerAddress;
        writeBuffer[1] = dataToSend;
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, 2, 1);
        return readBuffer[0];
    }

    @Override
    public synchronized void sendData(byte slaveAddress, byte[] dataToSend) {
        final int dataToSendLength = dataToSend.length;
        System.arraycopy(dataToSend, 0, writeBuffer, 0, dataToSendLength);
        I2CMasterDriver.sendData(registerSelector, slaveAddress, dataToSendLength);
    }

    @Override
    public synchronized void sendDataWithException(byte slaveAddress, byte[] dataToSend) throws DeviceIOException {
        final int dataToSendLength = dataToSend.length;
        System.arraycopy(dataToSend, 0, writeBuffer, 0, dataToSendLength);
        I2CMasterDriver.sendDataWithException(registerSelector, slaveAddress, dataToSendLength);

    }

    @Override
    public synchronized void receiveData(byte slaveAddress, int[] dataToReceive) {
        final int dataToReceiveLength = dataToReceive.length;
        I2CMasterDriver.receiveData(registerSelector, slaveAddress, dataToReceiveLength);
        System.arraycopy(readBuffer, 0, dataToReceive, 0, dataToReceiveLength);
    }

    @Override
    public synchronized void receiveDataWithException(byte slaveAddress, int[] dataToReceive) throws DeviceIOException {
        final int dataToReceiveLength = dataToReceive.length;
        I2CMasterDriver.receiveDataWithException(registerSelector, slaveAddress, dataToReceiveLength);
        System.arraycopy(readBuffer, 0, dataToReceive, 0, dataToReceiveLength);

    }

    @Override
    public synchronized void sendAndReceiveData(byte slaveAddress, byte[] dataToSend, int[] dataToReceive) {
        final int dataToSendLength = dataToSend.length;
        final int dataToReceiveLength = dataToReceive.length;
        System.arraycopy(dataToSend, 0, writeBuffer, 0, dataToSendLength);
        I2CMasterDriver.sendAndReceiveData(registerSelector, slaveAddress, dataToSendLength, dataToReceiveLength);
        System.arraycopy(readBuffer, 0, dataToReceive, 0, dataToReceiveLength);
    }

    @Override
    public synchronized void sendAndReceiveDataWithException(byte slaveAddress, byte[] dataToSend, int[] dataToReceive) throws DeviceIOException {
        final int dataToSendLength = dataToSend.length;
        final int dataToReceiveLength = dataToReceive.length;
        System.arraycopy(dataToSend, 0, writeBuffer, 0, dataToSendLength);
        I2CMasterDriver.sendAndReceiveDataWithException(registerSelector, slaveAddress, dataToSendLength, dataToReceiveLength);
        System.arraycopy(readBuffer, 0, dataToReceive, 0, dataToReceiveLength);
    }

}
