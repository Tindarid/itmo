package ru.ifmo.rain.valeyev.mapper;

import java.util.List;

public class ThreadUtils {
    public static void check(final int threads) {
        if (threads <= 0) {
            throw new IllegalArgumentException("Number of threads must be positive");
        }
    }

    public static void addWithStart(final List<Thread> threads, final Thread thread) {
        threads.add(thread);
        thread.start();
    }

    public static void interruptAll(final List<Thread> threads) {
        for (Thread thread : threads) {
            thread.interrupt();
        }
    }

    public static void joinAll(final List<Thread> threads) throws InterruptedException {
        for (Thread thread : threads) {
            thread.join();
        }
    }
}
