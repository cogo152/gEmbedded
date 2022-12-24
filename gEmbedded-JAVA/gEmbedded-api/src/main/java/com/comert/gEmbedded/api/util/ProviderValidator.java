package com.comert.gEmbedded.api.util;

import java.lang.reflect.Constructor;

public abstract class ProviderValidator {

    private static final String PARENT_CLASS_SUFFIX = "Parent";
    private static final int PARENT_CLASS_SUFFIX_LENGTH = PARENT_CLASS_SUFFIX.length();


    private ProviderValidator() {
    }

    public static Constructor<?> validateProvider(final Class<?> providerParentClass, final String fullQualifiedProviderClassName) throws ProviderException {
        if (providerParentClass == null) {
            throw new ProviderException(ProviderExceptionMessage.ARGUMENT_INVALID, "providerParentClass");
        }

        if (fullQualifiedProviderClassName == null) {
            throw new ProviderException(ProviderExceptionMessage.ARGUMENT_INVALID, "fullQualifiedProviderClassName");
        }

        final Class<?> providerClass;
        try {
            providerClass = Class.forName(fullQualifiedProviderClassName);
        } catch (ClassNotFoundException classNotFoundException) {
            throw new ProviderException(ProviderExceptionMessage.NOT_IN_IMPL_PACKAGE, fullQualifiedProviderClassName);
        }

        if (providerClass.getSuperclass() != providerParentClass) {
            throw new ProviderException(ProviderExceptionMessage.NOT_A_SUBCLASS, providerClass.getName());
        }

        try {
            return providerClass.getConstructor();
        } catch (NoSuchMethodException noSuchMethodException) {
            throw new ProviderException(ProviderExceptionMessage.NO_PUBLIC_DEFAULT_CONSTRUCTOR, providerClass.getName());
        }

    }

    public static Constructor<?> validateProvider(final Class<?> providerParentClass) throws ProviderException {
        if (providerParentClass == null || !providerParentClass.getSimpleName().contains(PARENT_CLASS_SUFFIX)) {
            throw new ProviderException(ProviderExceptionMessage.ARGUMENT_INVALID, "providerParentClass");
        }

        final var providerNameBuilder = new StringBuilder(providerParentClass.getName());
        providerNameBuilder.delete(providerNameBuilder.indexOf(PARENT_CLASS_SUFFIX), providerNameBuilder.indexOf(PARENT_CLASS_SUFFIX) + PARENT_CLASS_SUFFIX_LENGTH);

        return validateProvider(providerParentClass, providerNameBuilder.toString());
    }

}
