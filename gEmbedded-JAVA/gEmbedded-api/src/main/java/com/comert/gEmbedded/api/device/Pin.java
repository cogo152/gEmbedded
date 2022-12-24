package com.comert.gEmbedded.api.device;

public enum Pin implements DeviceConstant {

    PIN_0((byte) 0, "Zero"),
    PIN_1((byte) 1, "One"),
    PIN_2((byte) 2, "Two"),
    PIN_3((byte) 3, "Three"),
    PIN_4((byte) 4, "Four"),
    PIN_5((byte) 5, "Five"),
    PIN_6((byte) 6, "Six"),
    PIN_7((byte) 7, "Seven"),
    PIN_8((byte) 8, "Eight"),
    PIN_9((byte) 9, "Nine"),
    PIN_10((byte) 10, "Ten"),
    PIN_11((byte) 11, "Eleven"),
    PIN_12((byte) 12, "Twelve"),
    PIN_13((byte) 13, "Thirteen"),
    PIN_14((byte) 14, "Fourteen"),
    PIN_15((byte) 15, "Fifteen"),
    PIN_16((byte) 16, "Sixteen"),
    PIN_17((byte) 17, "Seventeen"),
    PIN_18((byte) 18, "Eighteen"),
    PIN_19((byte) 19, "Nineteen"),
    PIN_20((byte) 20, "Twenty"),
    PIN_21((byte) 21, "Twenty one"),
    PIN_22((byte) 22, "Twenty two"),
    PIN_23((byte) 23, "Twenty three"),
    PIN_24((byte) 24, "Twenty four"),
    PIN_25((byte) 25, "Twenty five"),
    PIN_26((byte) 26, "Twenty six"),
    PIN_27((byte) 27, "Twenty seven"),
    PIN_28((byte) 28, "Twenty eight"),
    PIN_29((byte) 29, "Twenty nine"),
    PIN_30((byte) 30, "Thirty");

    Pin(byte digit, String text) {
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
