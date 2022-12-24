package com.comert.gEmbedded.api.util;

import java.util.Arrays;

public abstract class InstanceCreationValidator {

    private InstanceCreationValidator() {
    }

    /**
     * Validates if the instance is constructed in desired class.
     * It forces user code to use factory class.
     * User can also create classes with new keyword. For example new InputPin(). But it causes that program looses control.
     *
     * @param desiredClass usually factory classes.
     * @throws InstanceCreationException if the class is not constructed via factory classes.
     */
    public static void validateIfInstanceIsBeingCreatedInDesiredClass(final Class<?> desiredClass) throws InstanceCreationException {
        if (desiredClass == null) {
            throw new InstanceCreationException(InstanceExceptionMessage.ARGUMENT_INVALID, "desiredClass");
        }

        final var result = Arrays.stream(Thread.currentThread().getStackTrace())
                .anyMatch(stackTraceElement -> stackTraceElement
                        .getClassName()
                        .equals(desiredClass.getName())
                );
        if (!result)
            throw new InstanceCreationException(InstanceExceptionMessage.OUT_OF_DESIRED_CLASS, desiredClass.getName());
    }

}
