package com.comert.gEmbedded.api.util;

import com.comert.gEmbedded.api.testutil.TestProvider;
import com.comert.gEmbedded.api.testutil.TestProviderParent;
import org.junit.jupiter.api.*;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.*;

/**
 * This test case verifies :
 * ProviderException.java
 * ProviderExceptionMessage.java
 * ProviderFactory.java
 * ProviderMessage.java
 */
@EnabledForJreRange(min = JRE.JAVA_17)
@TestMethodOrder(MethodOrderer.OrderAnnotation.class)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class ProviderFactoryUTest {
    private final Class<TestProviderParent> parentClass = TestProviderParent.class;

    private final String implPackage = parentClass.getPackageName()+".";

    @Order(1)
    @Test
    public void testFailWhenProviderFailsWhileConstruction() {
        /*
         * Assume that provider is valid but an error occurred while construction in JVM.
         * It throws exception when tries 3 times construction.
         * In the 4th time construction result is successful like a valid provider class.
         */

        final var validProviderClassName = implPackage + "TestProviderConstructionFails";

        for (int i = 0; i < 3; i++) {

            assertThatExceptionOfType(ProviderException.class)
                    .isThrownBy(
                            () -> ProviderFactory.createProviderAndUpcastToParentReference(parentClass, validProviderClassName)
                    )
                    .withMessage(
                            ProviderExceptionMessage.COULD_NOT_BE_CONSTRUCTED + " : " + validProviderClassName
                    );
        }

        assertDoesNotThrow(() -> ProviderFactory.createProviderAndUpcastToParentReference(parentClass, validProviderClassName));

    }

    @Order(2)
    @Test
    public void testSuccessWhenInstanceIsBeingCreated() {
        final var validProviderClassName = implPackage + "TestProvider";

        TestProviderParent toReferenceParentClass = null;
        try {
            toReferenceParentClass = ProviderFactory.createProviderAndUpcastToParentReference(parentClass, validProviderClassName);
        } catch (ProviderException providerException) {
            providerException.printStackTrace();
            fail("ProviderException should not be thrown");
        }

        assertNotNull(toReferenceParentClass);
        assertEquals(TestProvider.class, toReferenceParentClass.getClass());
        assertEquals(TestProviderParent.class, toReferenceParentClass.getClass().getSuperclass());

        toReferenceParentClass = null;

        try {
            toReferenceParentClass = ProviderFactory.createProviderAndUpcastToParentReference(parentClass);
        } catch (ProviderException providerException) {
            providerException.printStackTrace();
            fail("ProviderException should not be thrown");
        }

        assertNotNull(toReferenceParentClass);
        assertEquals(TestProvider.class, toReferenceParentClass.getClass());
        assertEquals(TestProviderParent.class, toReferenceParentClass.getClass().getSuperclass());
    }

}