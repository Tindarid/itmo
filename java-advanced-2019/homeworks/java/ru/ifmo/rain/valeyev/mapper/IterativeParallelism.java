package ru.ifmo.rain.valeyev.mapper;

import java.util.Comparator;
import java.util.function.Predicate;
import java.util.function.Function;
import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.Collections;
import java.util.NoSuchElementException;
import java.util.stream.Stream;
import java.util.stream.Collectors;

import info.kgeorgiy.java.advanced.concurrent.ListIP;
import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import ru.ifmo.rain.valeyev.mapper.ThreadUtils;

public class IterativeParallelism implements ListIP {
    private final ParallelMapper mapper;

    public IterativeParallelism() {
        mapper = null;
    }

    public IterativeParallelism(ParallelMapper mapper) {
        this.mapper = mapper;
    }

    private <T, R> List<R> resolve(int allowedThreads, final List<? extends T> values, 
                             final Function<List<? extends T>, ? extends R> task) throws InterruptedException {
        ThreadUtils.check(allowedThreads);
        final int size = values.size();
        final int usingThreads = Math.min(allowedThreads, size);
        final int block = size / usingThreads;
        final List<List<? extends T>> subTasks = new ArrayList<>(Collections.nCopies(usingThreads, null));
        for (int i = 0; i < usingThreads; ++i) {
            final int l = i * block;
            final int r = i == usingThreads - 1 ? size : (i + 1) * block;
            final int ind = i;
            subTasks.set(ind, values.subList(l, r));
        }
        if (mapper != null) {
            return mapper.map(task, subTasks);
        } else {
            return map(usingThreads, task, subTasks);
        }
    }

    private <T, R> List<R> map(final int usingThreads, final Function<List<? extends T>, ? extends R> task, final List<List<? extends T>> subTasks) throws InterruptedException {
        final List<R> result = new LinkedList<>(Collections.nCopies(usingThreads, null));
        final List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < usingThreads; ++i) {
            final int ind = i;
            ThreadUtils.addWithStart(threads, new Thread(() -> result.set(ind, task.apply(subTasks.get(ind)))));
        }
        ThreadUtils.joinAll(threads);
        return result;
    }

    private <T, R, U> R apply(int threads, List<? extends T> values,
            Function<List<? extends T>, ? extends U> task, Function<List<? extends U>, R> fold) throws InterruptedException {
        return fold.apply(resolve(threads, values, task));
    }

    public <T> T maximum(int threads, List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        if (values.isEmpty()) {
            throw new NoSuchElementException("List of values is empty");
        }
        Function<List<? extends T>, ? extends T> task = (list) -> Collections.max(list, comparator);
        return apply(threads, values, task, task);
    }

    public <T> T minimum(int threads, List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        return maximum(threads, values, Collections.reverseOrder(comparator));
    }

    public <T> boolean all(int threads, List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        Function<List<? extends T>, ? extends Boolean> task = (list) -> list.stream().allMatch(predicate);
        Function<List<? extends Boolean>, ? extends Boolean> fold = (list) -> list.stream().allMatch(e -> e);
        return apply(threads, values, task, fold);
    }

    public <T> boolean any(int threads, List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        return !all(threads, values, e -> !predicate.test(e));
    }

    public String join(int threads, List<?> values) throws InterruptedException {
        Function<List<?>, ? extends String> task = (list) -> list.stream().map(Object::toString).collect(Collectors.joining());
        Function<List<? extends String>, ? extends String> fold = (list) -> list.stream().collect(Collectors.joining());
        return apply(threads, values, task, fold);
    }

    public <T> List<T> filter(final int threads, final List<? extends T> values, final Predicate<? super T> predicate) throws InterruptedException {
        Function<List<? extends T>, ? extends List<T>> task = (list) -> list.stream().filter(predicate).collect(Collectors.toList());
        Function<List<? extends List<T>>, ? extends List<T>> fold = (list) -> list.stream().flatMap(x -> x.stream()).collect(Collectors.toList());
        return apply(threads, values, task, fold);
    }

    public <T, U> List<U> map(final int threads, final List<? extends T> values, final Function<? super T, ? extends U> f) throws InterruptedException {
        Function<List<? extends T>, ? extends List<? extends U>> task = (list) -> list.stream().map(f).collect(Collectors.toList());
        Function<List<? extends List<? extends U>>, ? extends List<U>> fold = (list) -> list.stream().flatMap(x -> x.stream()).collect(Collectors.toList());
        return apply(threads, values, task, fold);
    }
}
