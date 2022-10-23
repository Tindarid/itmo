package ru.ifmo.rain.valeyev.mapper;

import java.util.List;
import java.util.function.Function;
import java.util.Queue;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Collections;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import ru.ifmo.rain.valeyev.mapper.ThreadUtils;

public class ParallelMapperImpl implements ParallelMapper {
    private final Queue<Runnable> tasks;
    private final List<Thread> pool;

    public ParallelMapperImpl(int threads) {
        ThreadUtils.check(threads);
        tasks = new ArrayDeque<>();
        pool = new ArrayList<>();
        for (int i = 0; i < threads; ++i) {
            ThreadUtils.addWithStart(pool, 
                     new Thread(() -> {
                        while (!Thread.interrupted()) {
                            try {
                                pollTask();
                            } catch (InterruptedException e) {
                                break;
                            }
                        }
                     }));
        }
    }

    private class Results<R> {
        private final List<R> results;
        private int count;

        private Results(final int size) {
            results = new LinkedList<>(Collections.nCopies(size, null));
            count = 0;
        }

        private void set(final int ind, R res) {
            results.set(ind, res);
            synchronized(this) {
                count++;
                if (count == results.size()) {
                    notify();
                }
            }
        }

        private List<R> get() throws InterruptedException {
            synchronized(this) {
                while (count != results.size()) {
                    wait();
                }
            }
            return results;
        }
    }

    public <T, R> List<R> map(final Function<? super T, ? extends R> f, final List<? extends T> args) throws InterruptedException {
        final int size = args.size();
        Results<R> results = new Results(size);
        for (int i = 0; i < size; ++i) {
            final int temp = i;
            addTask(() -> results.set(temp, f.apply(args.get(temp))));
        }
        return results.get();
    }

    public void close() {
        ThreadUtils.interruptAll(pool);
        try {
            ThreadUtils.joinAll(pool);
        } catch (InterruptedException e) {
            //
        }
    }

    private void addTask(final Runnable task) throws InterruptedException {
        synchronized(tasks) {
            tasks.add(task);
            tasks.notify();
        }
    }

    private void pollTask() throws InterruptedException {
        Runnable task;
        synchronized(tasks) {
            while (tasks.isEmpty()) {
                tasks.wait();
            }
            task = tasks.poll();
        }
        task.run();
    }
}
