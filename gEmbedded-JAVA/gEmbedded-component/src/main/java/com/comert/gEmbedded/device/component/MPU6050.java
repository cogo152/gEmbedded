package com.comert.gEmbedded.device.component;

import com.comert.gEmbedded.api.device.DeviceIOException;
import com.comert.gEmbedded.api.device.i2c.I2CMaster;

public final class MPU6050 extends Thread {

    // Register Addresses
    private static final byte REGISTER_AUX_VDDIO = 0x01;
    private static final byte REGISTER_SMPLRT_DIV = 0x19;
    private static final byte REGISTER_CONFIG = 0x1A;
    private static final byte REGISTER_GYRO_CONFIG = 0x1B;
    private static final byte REGISTER_ACCEL_CONFIG = 0x1C;
    private static final byte REGISTER_FF_THR = 0x1D;
    private static final byte REGISTER_FF_DUR = 0x1E;
    private static final byte REGISTER_MOT_THR = 0x1F;
    private static final byte REGISTER_MOT_DUR = 0x20;
    private static final byte REGISTER_ZRMOT_THR = 0x21;
    private static final byte REGISTER_ZRMOT_DUR = 0x22;
    private static final byte REGISTER_FIFO_EN = 0x23;
    private static final byte REGISTER_I2C_MST_CTRL = 0x24;
    private static final byte REGISTER_I2C_SLV0_ADDR = 0x25;
    private static final byte REGISTER_I2C_SLV0_REG = 0x26;
    private static final byte REGISTER_I2C_SLV0_CTRL = 0x27;
    private static final byte REGISTER_I2C_SLV1_ADDR = 0x28;
    private static final byte REGISTER_I2C_SLV1_REG = 0x29;
    private static final byte REGISTER_I2C_SLV1_CTRL = 0x2A;
    private static final byte REGISTER_I2C_SLV2_ADDR = 0x2B;
    private static final byte REGISTER_I2C_SLV2_REG = 0x2C;
    private static final byte REGISTER_I2C_SLV2_CTRL = 0x2D;
    private static final byte REGISTER_I2C_SLV3_ADDR = 0x2E;
    private static final byte REGISTER_I2C_SLV3_REG = 0x2F;
    private static final byte REGISTER_I2C_SLV3_CTRL = 0x30;
    private static final byte REGISTER_I2C_SLV4_ADDR = 0x31;
    private static final byte REGISTER_I2C_SLV4_REG = 0x32;
    private static final byte REGISTER_I2C_SLV4_DO = 0x33;
    private static final byte REGISTER_I2C_SLV4_CTRL = 0x34;
    private static final byte REGISTER_I2C_SLV4_DI = 0x35;
    private static final byte REGISTER_I2C_MST_STATUS = 0x36;
    private static final byte REGISTER_INT_PIN_CFG = 0x37;
    private static final byte REGISTER_INT_ENABLE = 0x38;
    private static final byte REGISTER_INT_STATUS = 0x3A;
    private static final byte REGISTER_ACCEL_XOUT_H = 0x3B;
    private static final byte REGISTER_ACCEL_XOUT_L = 0x3C;
    private static final byte REGISTER_ACCEL_YOUT_H = 0x3D;
    private static final byte REGISTER_ACCEL_YOUT_L = 0x3E;
    private static final byte REGISTER_ACCEL_ZOUT_H = 0x3F;
    private static final byte REGISTER_ACCEL_ZOUT_L = 0x40;
    private static final byte REGISTER_TEMP_OUT_H = 0x41;
    private static final byte REGISTER_TEMP_OUT_L = 0x42;
    private static final byte REGISTER_GYRO_XOUT_H = 0x43;
    private static final byte REGISTER_GYRO_XOUT_L = 0x44;
    private static final byte REGISTER_GYRO_YOUT_H = 0x45;
    private static final byte REGISTER_GYRO_YOUT_L = 0x46;
    private static final byte REGISTER_GYRO_ZOUT_H = 0x47;
    private static final byte REGISTER_GYRO_ZOUT_L = 0x48;
    private static final byte REGISTER_EXT_SENS_DATA_00 = 0x49;
    private static final byte REGISTER_EXT_SENS_DATA_01 = 0x4A;
    private static final byte REGISTER_EXT_SENS_DATA_02 = 0x4B;
    private static final byte REGISTER_EXT_SENS_DATA_03 = 0x4C;
    private static final byte REGISTER_EXT_SENS_DATA_04 = 0x4D;
    private static final byte REGISTER_EXT_SENS_DATA_05 = 0x4E;
    private static final byte REGISTER_EXT_SENS_DATA_06 = 0x4F;
    private static final byte REGISTER_EXT_SENS_DATA_07 = 0x50;
    private static final byte REGISTER_EXT_SENS_DATA_08 = 0x51;
    private static final byte REGISTER_EXT_SENS_DATA_09 = 0x52;
    private static final byte REGISTER_EXT_SENS_DATA_10 = 0x53;
    private static final byte REGISTER_EXT_SENS_DATA_11 = 0x54;
    private static final byte REGISTER_EXT_SENS_DATA_12 = 0x55;
    private static final byte REGISTER_EXT_SENS_DATA_13 = 0x56;
    private static final byte REGISTER_EXT_SENS_DATA_14 = 0x57;
    private static final byte REGISTER_EXT_SENS_DATA_15 = 0x58;
    private static final byte REGISTER_EXT_SENS_DATA_16 = 0x59;
    private static final byte REGISTER_EXT_SENS_DATA_17 = 0x5A;
    private static final byte REGISTER_EXT_SENS_DATA_18 = 0x5B;
    private static final byte REGISTER_EXT_SENS_DATA_19 = 0x5C;
    private static final byte REGISTER_EXT_SENS_DATA_20 = 0x5D;
    private static final byte REGISTER_EXT_SENS_DATA_21 = 0x5E;
    private static final byte REGISTER_EXT_SENS_DATA_22 = 0x5F;
    private static final byte REGISTER_EXT_SENS_DATA_23 = 0x60;
    private static final byte REGISTER_MOT_DETECT_STATUS = 0x61;
    private static final byte REGISTER_I2C_SLV0_DO = 0x63;
    private static final byte REGISTER_I2C_SLV1_DO = 0x64;
    private static final byte REGISTER_I2C_SLV2_DO = 0x65;
    private static final byte REGISTER_I2C_SLV3_DO = 0x66;
    private static final byte REGISTER_I2C_MST_DELAY_CTRL = 0x67;
    private static final byte REGISTER_SIGNAL_PATH_RESET = 0x68;
    private static final byte REGISTER_MOT_DETECT_CTRL = 0x69;
    private static final byte REGISTER_USER_CTRL = 0x6A;
    private static final byte REGISTER_PWR_MGMT_1 = 0x6B;
    private static final byte REGISTER_PWR_MGMT_2 = 0x6C;
    private static final byte REGISTER_FIFO_COUNTH = 0x72;
    private static final byte REGISTER_FIFO_COUNTL = 0x73;
    private static final byte REGISTER_FIFO_R_W = 0x74;
    private static final byte REGISTER_WHO_AM_I = 0x75;

    // Default config settings
    private static final byte DEFAULT_SLAVE_ADDRESS = 0x68;
    private static final byte DEFAULT_PWM_MGMT_1_CONFIG = 0x00;
    private static final byte DEFAULT_PWM_MGMT_2_CONFIG = 0x00;
    private static final byte DEFAULT_CONFIG = 0x06;
    private static final byte DEFAULT_GYRO_CONFIG = 0x00;
    private static final byte DEFAULT_ACCEL_CONFIG = 0x00;
    private static final byte DEFAULT_SMPLRT_DIV = 0x00;
    private static final byte DEFAULT_INT_ENABLE_CONFIG = 0x00;
    private static final double DEFAULT_ACCEL_LSB_SENSITIVITY = 16384.;
    private static final double DEFAULT_GYRO_LSB_SENSITIVITY = 131.;

    // Config Variables
    private final I2CMaster master;
    private final byte slaveAddress;
    private final byte pwrMgmt1Config;
    private final byte pwrMgmt2Config;
    private final byte config;
    private final byte gyroConfig;
    private final byte accelConfig;
    private final byte smplrtDiv;
    private final byte intEnableConfig;
    private final int calibrationTimes;
    private final int calibrationSleepInMilSec;

    // Thread variables
    private volatile boolean running;
    private volatile long lastUpdateTime = 0;
    private final int valueUpdateSleepInMilSec;

    // Sensor variables
    private final double accelLSBSensitivity;
    private final double gyroLSBSensitivity;
    private final double radianToDegree = 180. / Math.PI;

    private final double[] gyroCalibrationValues = new double[3];
    private final double[] gyroValues = new double[3];


    public MPU6050(I2CMaster master) {
        this(master, DEFAULT_SLAVE_ADDRESS, DEFAULT_PWM_MGMT_1_CONFIG, DEFAULT_PWM_MGMT_2_CONFIG, DEFAULT_CONFIG, DEFAULT_GYRO_CONFIG, DEFAULT_ACCEL_CONFIG, DEFAULT_SMPLRT_DIV);
    }

    public MPU6050(I2CMaster master, byte slaveAddress, byte pwrMgmt1Config, byte pwrMgmt2Config, byte config, byte gyroConfig, byte accelConfig, byte smplrtDiv) {
        this.master = master;
        this.slaveAddress = slaveAddress;
        this.pwrMgmt1Config = pwrMgmt1Config;
        this.pwrMgmt2Config = pwrMgmt2Config;
        this.config = config;
        this.gyroConfig = gyroConfig;
        this.accelConfig = accelConfig;
        this.smplrtDiv = smplrtDiv;
        this.intEnableConfig = DEFAULT_INT_ENABLE_CONFIG;
        this.accelLSBSensitivity = DEFAULT_ACCEL_LSB_SENSITIVITY;
        this.gyroLSBSensitivity = DEFAULT_GYRO_LSB_SENSITIVITY;
        this.calibrationTimes = 100;
        this.calibrationSleepInMilSec = 10;
        this.valueUpdateSleepInMilSec = 1;

        try {
            connectDevice();
            System.out.println("Connection successful");
        } catch (DeviceIOException ioException) {
            throw new RuntimeException("MPU6050 device connection failed");
        }

        try {
            configureConfigRegisters();
            System.out.println("Configuration successful");
        } catch (DeviceIOException ioException) {
            throw new RuntimeException("MPU6050 device configuration failed");
        }

        try {
            setGyroCalibrationValues();
            System.out.println("Calibration successful");
        } catch (DeviceIOException ioException) {
            throw new RuntimeException("MPU6050 device calibration failed please retry");
        }
    }

    private void connectDevice() throws DeviceIOException {
        final int answer = master.readRegister(slaveAddress, REGISTER_WHO_AM_I);
        if (answer != slaveAddress) {
            throw new RuntimeException("MPU6050 device could not be found");
        }
    }

    private void configureConfigRegisters() throws DeviceIOException {
        configureRegister(REGISTER_PWR_MGMT_1, pwrMgmt1Config);
        configureRegister(REGISTER_PWR_MGMT_2, pwrMgmt2Config);
        configureRegister(REGISTER_CONFIG, config);
        configureRegister(REGISTER_GYRO_CONFIG, gyroConfig);
        configureRegister(REGISTER_ACCEL_CONFIG, accelConfig);
        configureRegister(REGISTER_SMPLRT_DIV, smplrtDiv);
        configureRegister(REGISTER_INT_ENABLE, intEnableConfig);
    }

    private void setGyroCalibrationValues() throws DeviceIOException {
        for (int i = 0; i < calibrationTimes; i++) {
            gyroCalibrationValues[0] += readRegisters(REGISTER_GYRO_XOUT_H, REGISTER_GYRO_XOUT_L) / gyroLSBSensitivity;
            gyroCalibrationValues[1] += readRegisters(REGISTER_GYRO_YOUT_H, REGISTER_GYRO_YOUT_L) / gyroLSBSensitivity;
            gyroCalibrationValues[2] += readRegisters(REGISTER_GYRO_ZOUT_H, REGISTER_GYRO_ZOUT_L) / gyroLSBSensitivity;
        }
        gyroCalibrationValues[0] /= calibrationTimes;
        gyroCalibrationValues[1] /= calibrationTimes;
        gyroCalibrationValues[2] /= calibrationTimes;
    }

    public void updateGyroValues(){
        try {
            gyroValues[0] += (((readRegisters(REGISTER_GYRO_XOUT_H, REGISTER_GYRO_XOUT_L) / gyroLSBSensitivity) - gyroCalibrationValues[0])/182.04);
            gyroValues[1] += (((readRegisters(REGISTER_GYRO_YOUT_H, REGISTER_GYRO_YOUT_L) / gyroLSBSensitivity) - gyroCalibrationValues[1])/182.04);
            gyroValues[2] += (((readRegisters(REGISTER_GYRO_ZOUT_H, REGISTER_GYRO_ZOUT_L) / gyroLSBSensitivity) - gyroCalibrationValues[2])/182.04);
        } catch (DeviceIOException ioException){
        }

    }

    public double[] getGyroValues(){
        return gyroValues;
    }

    private void configureRegister(final byte registerAddress, final byte data) throws DeviceIOException {
        master.writeRegister(slaveAddress, registerAddress, data);
    }

    private int readRegisters(final byte highRegisterAddress, final byte lowRegisterAddress) throws DeviceIOException {
        int value;
        final var high = master.readRegister(slaveAddress, highRegisterAddress);
        final var low = master.readRegister(slaveAddress, lowRegisterAddress);
        value = (high << 8) | (low);
        if (value >= 32768) {
            value = -(65536 - value);
        }
        return value;
    }

    @Override
    public void run() {
        while (running) {
            try {
                updateGyroValues();
                Thread.sleep(valueUpdateSleepInMilSec);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void startMPU6050() {
        running = true;
        this.start();
        lastUpdateTime = System.currentTimeMillis();
    }

    public void stopMPU6050() {
        running = false;
        try {
            join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

}