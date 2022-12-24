package com.comert.gEmbedded.api.util;

import com.comert.gEmbedded.api.ApplicationException;

public final class InstanceCreationException extends ApplicationException {

    public InstanceCreationException(InstanceMessage instanceMessage, String property) {
        super(instanceMessage, property);
    }

}
