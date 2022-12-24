package com.comert.gEmbedded.api.device;

import com.comert.gEmbedded.api.ApplicationException;
public class DeviceExecutionException extends ApplicationException {

    public DeviceExecutionException(DeviceExecutionMessage deviceExecutionMessage, String property) {
        super(deviceExecutionMessage, property);
    }

}
