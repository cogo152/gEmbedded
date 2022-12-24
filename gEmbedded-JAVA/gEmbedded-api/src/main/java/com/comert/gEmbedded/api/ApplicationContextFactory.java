package com.comert.gEmbedded.api;

import com.comert.gEmbedded.api.device.DeviceContext;
import com.comert.gEmbedded.api.util.ProviderException;
import com.comert.gEmbedded.api.device.provider.DeviceContextProviderParent;
import com.comert.gEmbedded.api.util.ProviderFactory;

public abstract class ApplicationContextFactory {

    private static DeviceContextProviderParent deviceContextProvider;

    private ApplicationContextFactory() {
    }

    /**
     * @return DeviceContext
     * @throws RuntimeException if provider does not obey the api rules.
     */
    public static synchronized DeviceContext getDeviceContextInstance() {
        if (deviceContextProvider == null) {
            final var providerParentClass = DeviceContextProviderParent.class;
            try {
                deviceContextProvider = ProviderFactory.createProviderAndUpcastToParentReference(providerParentClass);
            } catch (ProviderException providerException) {
                throw new RuntimeException(providerException.getMessage());
            }
        }
        return deviceContextProvider;
    }

}
