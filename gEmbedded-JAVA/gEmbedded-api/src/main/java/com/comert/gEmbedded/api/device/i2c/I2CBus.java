package com.comert.gEmbedded.api.device.i2c;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum I2CBus implements DeviceConstant {

    BUS_0((byte) 0, "Bus 0"),

    BUS_1((byte) 1, "Bus 1"),

    BUS_2((byte) 2, "Bus 2");

    I2CBus(byte digit, String text) {
        this.digit = digit;
        this.text = text;
    }

    private final byte digit;

    private final String text;

    @Override
    public byte getDigit() {
        return digit;
    }

    @Override
    public String getText() {
        return text;
    }
}
