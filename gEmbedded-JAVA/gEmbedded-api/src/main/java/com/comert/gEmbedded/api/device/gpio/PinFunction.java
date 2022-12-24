package com.comert.gEmbedded.api.device.gpio;

import com.comert.gEmbedded.api.device.DeviceConstant;

public enum PinFunction implements DeviceConstant {

    ANALOG_INPUT((byte) 0, "Analog Input"),
    ANALOG_OUTPUT((byte) 1, "Analog Output"),
    DIGITAL_INPUT((byte) 2, "Digital Input"),
    DIGITAL_OUTPUT((byte) 3, "Digital Output"),
    ALT_0((byte) 4, "Alternate 0"),
    ALT_1((byte) 5, "Alternate 1"),
    ALT_2((byte) 6, "Alternate 2"),
    ALT_3((byte) 7, "Alternate 3"),
    ALT_4((byte) 8, "Alternate 4"),
    ALT_5((byte) 9, "Alternate 5"),
    ALT_6((byte) 10, "Alternate 6");

    PinFunction(byte digit, String text) {
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
