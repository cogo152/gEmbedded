package com.comert.gEmbedded.api.device.pwm;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PWMSilence implements DeviceConstant {

    LOW((byte) 0, "Low"),
    HIGH((byte) 1, "High");

    PWMSilence(byte digit, String text) {
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
