package com.comert.gEmbedded.api.util;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

public abstract class ProviderFactory {

    private ProviderFactory() {
    }

    public static <P> P createProviderAndUpcastToParentReference(final Class<P> providerParentClass, final String fullQualifiedProviderClassName) throws ProviderException {
        final Constructor<?> providerConstructor = ProviderValidator.validateProvider(providerParentClass, fullQualifiedProviderClassName);
        return upCastProviderClassToParentReference(providerConstructor, providerParentClass);
    }

    public static <P> P createProviderAndUpcastToParentReference(final Class<P> providerParentClass) throws ProviderException {
        final Constructor<?> providerConstructor = ProviderValidator.validateProvider(providerParentClass);
        return upCastProviderClassToParentReference(providerConstructor, providerParentClass);
    }

    private static <P> P upCastProviderClassToParentReference(Constructor<?> providerConstructor, final Class<P> providerParentClass) throws ProviderException {
        if (providerConstructor == null) {
            throw new ProviderException(ProviderExceptionMessage.ARGUMENT_INVALID, "providerConstructor");
        }

        if (providerParentClass == null) {
            throw new ProviderException(ProviderExceptionMessage.ARGUMENT_INVALID, "providerParentClass");
        }

        P parentReference;
        try {
            parentReference = providerParentClass.cast(providerConstructor.newInstance());
        } catch (InstantiationException | IllegalAccessException | InvocationTargetException e) {
            throw new ProviderException(ProviderExceptionMessage.COULD_NOT_BE_CONSTRUCTED, providerConstructor.getName());
        }
        return parentReference;
    }

}
