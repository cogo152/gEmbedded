package com.comert.gEmbedded.api.device.i2c;

import com.comert.gEmbedded.api.device.DeviceIOException;

public interface I2CMaster {

    void writeSlave(byte slaveAddress, byte dataToSend);

    void writeSlaveWithException(byte slaveAddress, byte dataToSend) throws DeviceIOException;

    int readSlave(byte slaveAddress);

    int readSlaveWithException(byte slaveAddress) throws DeviceIOException;

    int writeAndReadSlave(byte slaveAddress, byte dataToSend);

    int writeAndReadSlaveWithException(byte slaveAddress, byte dataToSend) throws DeviceIOException;

    void writeRegister(byte slaveAddress, byte registerAddress, byte dataToSend);

    void writeRegisterWithException(byte slaveAddress, byte registerAddress, byte dataToSend) throws DeviceIOException;

    int readRegister(byte slaveAddress, byte registerAddress);

    int readRegisterWithException(byte slaveAddress, byte registerAddress) throws DeviceIOException;

    int writeAndReadRegister(byte slaveAddress, byte registerAddress, byte dataToSend);

    int writeAndReadRegisterWithException(byte slaveAddress, byte registerAddress, byte dataToSend) throws DeviceIOException;

    void sendData(byte slaveAddress, byte[] dataToSend);

    void sendDataWithException(byte slaveAddress, byte[] dataToSend) throws DeviceIOException;

    void receiveData(byte slaveAddress, int[] dataToReceive);

    void receiveDataWithException(byte slaveAddress, int[] dataToReceive) throws DeviceIOException;

    void sendAndReceiveData(byte slaveAddress, byte[] dataToSend, int[] dataToReceive);

    void sendAndReceiveDataWithException(byte slaveAddress, byte[] dataToSend, int[] dataToReceive) throws DeviceIOException;

}
