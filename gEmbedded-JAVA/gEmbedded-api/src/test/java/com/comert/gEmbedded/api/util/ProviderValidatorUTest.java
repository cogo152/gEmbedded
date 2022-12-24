package com.comert.gEmbedded.api.util;

import com.comert.gEmbedded.api.testutil.TestProviderParent;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Constructor;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.*;

public class ProviderValidatorUTest {

    private final Class<TestProviderParent> parentClass = TestProviderParent.class;

    private final String implPackage = parentClass.getPackageName() + ".";

    @Order(1)
    @Test
    public void testFailWhenArgumentsAreIllegal() {
        assertThatExceptionOfType(ProviderException.class)
                .isThrownBy(
                        () -> ProviderValidator.validateProvider(null, "Not null class name")
                )
                .withMessage(
                        ProviderExceptionMessage.ARGUMENT_INVALID + " : " + "providerParentClass"
                );

        assertThatExceptionOfType(ProviderException.class)
                .isThrownBy(
                        () -> ProviderValidator.validateProvider(Object.class, null)
                )
                .withMessage(
                        ProviderExceptionMessage.ARGUMENT_INVALID + " : " + "fullQualifiedProviderClassName"
                );

        assertThatExceptionOfType(ProviderException.class)
                .isThrownBy(
                        () -> ProviderValidator.validateProvider(null)
                )
                .withMessage(
                        ProviderExceptionMessage.ARGUMENT_INVALID + " : " + "providerParentClass"
                );

        assertThatExceptionOfType(ProviderException.class)
                .isThrownBy(
                        // Any class which does not contain "Parent" word in class name.
                        () -> ProviderValidator.validateProvider(Object.class)
                )
                .withMessage(
                        ProviderExceptionMessage.ARGUMENT_INVALID + " : " + "providerParentClass"
                );
    }

    @Order(2)
    @Test
    public void testFailWhenProviderIsNotInThePackage() {
        final var invalidProviderClassName = implPackage + "ThereIsNoProviderClass";

        assertThatExceptionOfType(ProviderException.class)
                .isThrownBy(
                        () -> ProviderValidator.validateProvider(parentClass, invalidProviderClassName)
                )
                .withMessage(
                        ProviderExceptionMessage.NOT_IN_IMPL_PACKAGE + " : " + invalidProviderClassName
                );
    }

    @Order(3)
    @Test
    public void testFailWhenProviderIsNotAChildClass() {
        final var invalidProviderClassName = implPackage + "TestProviderIsNotASubclass";

        assertThatExceptionOfType(ProviderException.class)
                .isThrownBy(
                        () -> ProviderValidator.validateProvider(parentClass, invalidProviderClassName)
                )
                .withMessage(
                        ProviderExceptionMessage.NOT_A_SUBCLASS + " : " + invalidProviderClassName
                );
    }

    @Order(4)
    @Test
    public void testFailWhenProviderDoesNotHaveAPublicDefaultConstructor() {
        final var invalidProviderClassName = implPackage + "TestProviderInvalidConstructor";

        assertThatExceptionOfType(ProviderException.class)
                .isThrownBy(
                        () -> ProviderValidator.validateProvider(parentClass, invalidProviderClassName)
                )
                .withMessage(
                        ProviderExceptionMessage.NO_PUBLIC_DEFAULT_CONSTRUCTOR + " : " + invalidProviderClassName
                );
    }

    @Order(5)
    @Test
    public void testSuccessWhenProviderIsValid() {
        final var validProviderClassName = implPackage + "TestProvider";

        Constructor<?> providerConstructor = null;
        try {
            providerConstructor = ProviderValidator.validateProvider(parentClass, validProviderClassName);
        } catch (ProviderException providerException) {
            providerException.printStackTrace();
            fail("ProviderException should not be thrown");
        }

        assertNotNull(providerConstructor);
        assertEquals(validProviderClassName, providerConstructor.getName());

        providerConstructor = null;
        try {
            providerConstructor = ProviderValidator.validateProvider(parentClass);
        } catch (ProviderException providerException) {
            providerException.printStackTrace();
            fail("ProviderException should not be thrown");
        }

        assertNotNull(providerConstructor);
        assertEquals(validProviderClassName, providerConstructor.getName());
    }

}
