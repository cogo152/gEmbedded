package com.comert.gEmbedded.api.device.pwm;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PWMPolarity implements DeviceConstant {

    LOW_HIGH((byte) 0, "Low-High"),
    HIGH_LOW((byte) 1, "High-Low");

    PWMPolarity(byte digit, String text) {
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
