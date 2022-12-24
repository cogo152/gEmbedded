package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PullUpDown implements DeviceConstant {

    NONE((byte) 0, "None"),
    PULL_UP((byte) 1, "Pull up"),
    PULL_DOWN((byte) 2, "Pull Down");

    PullUpDown(byte digit, String text) {
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
