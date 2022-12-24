package com.comert.gEmbedded.api.util;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.condition.EnabledForJreRange;
import org.junit.jupiter.api.condition.JRE;

import java.util.Arrays;

import static org.assertj.core.api.Assertions.assertThatExceptionOfType;
import static org.junit.jupiter.api.Assertions.fail;

/**
 * This test case verifies :
 * InstanceCreationException.java
 * InstanceCreationValidator.java
 * InstanceExceptionMessage.java
 * InstanceMessage.java
 */
@EnabledForJreRange(min = JRE.JAVA_17)
@TestInstance(value = TestInstance.Lifecycle.PER_CLASS)
public class InstanceCreationValidatorUTest {

    @Test
    public void testFailWhenArgumentIsInvalid() {
        final Class<Object> invalidArgument = null;

        assertThatExceptionOfType(InstanceCreationException.class)
                .isThrownBy(
                        () -> InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(invalidArgument)
                )
                .withMessage(
                        InstanceExceptionMessage.ARGUMENT_INVALID + " : " + "desiredClass"
                );
    }

    @Test
    public void testFailWhenInstanceIsNotBeingCreatedInDesiredClass() {
        final var notDesiredClass = Object.class;

        assertThatExceptionOfType(InstanceCreationException.class)
                .isThrownBy(
                        () -> InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(notDesiredClass)
                )
                .withMessage(
                        InstanceExceptionMessage.OUT_OF_DESIRED_CLASS + " : " + notDesiredClass.getName()
                );
    }

    @Test
    public void testSuccessWhenInstanceIsBeingCreatedInDesiredClass() {
        final var desiredClass = this.getClass();

        try {
            InstanceCreationValidator.validateIfInstanceIsBeingCreatedInDesiredClass(desiredClass);
        } catch (InstanceCreationException instanceCreationException) {
            instanceCreationException.printStackTrace();
            fail("Exception should not be thrown");
        }
    }

}