package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum Event implements DeviceConstant {

    SYNCHRONOUS_FALLING((byte) 0, "Synchronous Falling"),
    SYNCHRONOUS_RISING((byte) 1, "Synchronous Rising"),
    SYNCHRONOUS_BOTH((byte) 2, "Synchronous Both"),
    ASYNCHRONOUS_FALLING((byte) 3, "Asynchronous Falling"),
    ASYNCHRONOUS_RISING((byte) 4, "Asynchronous Rising"),
    ASYNCHRONOUS_BOTH((byte) 5, "Asynchronous Both");

    Event(byte digit, String text) {
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
