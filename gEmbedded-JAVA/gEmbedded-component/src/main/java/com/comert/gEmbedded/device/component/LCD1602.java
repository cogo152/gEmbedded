package com.comert.gEmbedded.device.component;

import com.comert.gEmbedded.api.device.DeviceIOException;
import com.comert.gEmbedded.api.device.i2c.I2CMaster;

public final class LCD1602 {

    private final byte LCD_CLEARDISPLAY = (byte) 0x01;
    private final byte LCD_ENTRYMODESET = (byte) 0x04;
    private final byte LCD_DISPLAYCONTROL = (byte) 0x08;
    private final byte LCD_FUNCTIONSET = (byte) 0x20;
    private final byte LCD_ENTRYLEFT = (byte) 0x02;
    private final byte LCD_DISPLAYON = (byte) 0x04;
    private final byte LCD_4BITMODE = (byte) 0x00;
    private final byte LCD_2LINE = (byte) 0x08;
    private final byte LCD_5x8DOTS = (byte) 0x00;
    private final byte LCD_BACKLIGHT = (byte) 0x08;
    private final byte En = (byte) 0b00000100;
    private final byte Rs = (byte) 0b00000001;

    private final I2CMaster master;
    private final byte slaveAddress;

    public LCD1602(I2CMaster master, byte slaveAddress) throws DeviceIOException, InterruptedException {
        this.master = master;
        this.slaveAddress = slaveAddress;
        init();
    }

    private void init() throws DeviceIOException, InterruptedException {
        lcdWrite((byte) 0x03);
        lcdWrite((byte) 0x03);
        lcdWrite((byte) 0x03);
        lcdWrite((byte) 0x02);

        lcdWrite((byte) (LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS | LCD_4BITMODE));
        lcdWrite((byte) (LCD_DISPLAYCONTROL | LCD_DISPLAYON));
        lcdWrite((byte) (LCD_CLEARDISPLAY));
        lcdWrite((byte) (LCD_ENTRYMODESET | LCD_ENTRYLEFT));
        Thread.sleep(0, 200000);
        display("Distance in cm", 1);
    }

    private void writeCommand(byte command) throws DeviceIOException, InterruptedException {
        master.writeSlave(this.slaveAddress, command);
        Thread.sleep(0, 100000);
    }

    private void strobe(byte data) throws DeviceIOException, InterruptedException {
        writeCommand((byte) (data | En | LCD_BACKLIGHT));
        Thread.sleep(0, 500000);
        writeCommand((byte) ((data & ~En) | LCD_BACKLIGHT));
        Thread.sleep(0, 100000);
    }

    private void writeFourBits(byte data) throws DeviceIOException, InterruptedException {
        writeCommand((byte) (data | LCD_BACKLIGHT));
        strobe(data);
    }

    private void lcdWrite(byte cmd, byte mode) throws DeviceIOException, InterruptedException {
        writeFourBits((byte) (mode | (cmd & 0xF0)));
        writeFourBits((byte) (mode | ((cmd << 4) & 0xF0)));
    }

    private void lcdWrite(byte cmd) throws DeviceIOException, InterruptedException {
        lcdWrite(cmd, (byte) 0);
    }

    public void display(String data, int line) throws DeviceIOException, InterruptedException {
        switch (line) {
            case 1 -> lcdWrite((byte) 0x80);
            case 2 -> lcdWrite((byte) 0xC0);
            case 3 -> lcdWrite((byte) 0x94);
            case 4 -> lcdWrite((byte) 0xD4);
        }
        for (int i = 0; i < data.length(); i++) {
            lcdWrite((byte) data.charAt(i), Rs);
        }
    }
}
