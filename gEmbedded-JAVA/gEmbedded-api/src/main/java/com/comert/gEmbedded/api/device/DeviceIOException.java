package com.comert.gEmbedded.api.device;

import com.comert.gEmbedded.api.ApplicationException;

public class DeviceIOException extends ApplicationException {

    public DeviceIOException(String message) {
        super(message);
    }

    public DeviceIOException(DeviceIOMessage deviceIOMessage, String property) {
        super(deviceIOMessage, property);
    }

}
