package com.comert.gEmbedded.api.testutil;

import org.junit.jupiter.api.Disabled;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

@Disabled
public abstract class MultiThreadingTest {

    private static int executedThreadSize;

    public synchronized static <I> int instanceSize(InstanceProducer<I> producer) throws InterruptedException {
        Set<I> instanceSet = Collections.synchronizedSet(new HashSet<>());

        Runnable runnable = () -> {
            I instance = producer.getInstance();
            instanceSet.add(instance);
            executedThreadSize++;
        };

        Thread thread1 = new Thread(runnable);
        Thread thread2 = new Thread(runnable);
        Thread thread3 = new Thread(runnable);
        Thread thread4 = new Thread(runnable);
        Thread thread5 = new Thread(runnable);
        Thread thread6 = new Thread(runnable);
        Thread thread7 = new Thread(runnable);
        Thread thread8 = new Thread(runnable);
        Thread thread9 = new Thread(runnable);
        Thread thread10 = new Thread(runnable);

        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();
        thread5.start();
        thread6.start();
        thread7.start();
        thread8.start();
        thread9.start();
        thread10.start();

        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        thread5.join();
        thread6.join();
        thread7.join();
        thread8.join();
        thread9.join();
        thread10.join();

        assert executedThreadSize == 10 : "Multithreading test fails because the thread size is equal to max size : 10";

        executedThreadSize = 0;

        return instanceSet.size();
    }

}
