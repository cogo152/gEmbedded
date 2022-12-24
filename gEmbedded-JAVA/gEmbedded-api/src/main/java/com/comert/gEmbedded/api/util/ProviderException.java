package com.comert.gEmbedded.api.util;

import com.comert.gEmbedded.api.ApplicationException;
public final class ProviderException extends ApplicationException {
    public ProviderException(ProviderMessage providerMessage, String property) {
        super(providerMessage, property);
    }

}
