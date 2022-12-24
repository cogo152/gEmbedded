package com.comert.gEmbedded.api.testutil;

import org.junit.jupiter.api.Disabled;

import java.lang.reflect.InvocationTargetException;

@Disabled
public class TestProviderConstructionFails extends TestProviderParent{

    private static int constructionTime = 0;

    public TestProviderConstructionFails() throws Exception {

        constructionTime++;

        switch (constructionTime) {
            case 1 -> {
                throw new InstantiationException();
            }
            case 2 -> {
                throw new IllegalAccessException();
            }
            case 3 -> {
                throw new InvocationTargetException(new Throwable());
            }
            default -> {
                return;
            }
        }
    }

}
