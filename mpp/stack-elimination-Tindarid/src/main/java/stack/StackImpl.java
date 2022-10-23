package stack;

import kotlinx.atomicfu.AtomicArray;
import kotlinx.atomicfu.AtomicRef;
import java.util.Random;

public class StackImpl implements Stack {
    private static class Node {
        final AtomicRef<Node> next;
        final int x;

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }

    // head pointer
    private final AtomicRef<Node> head = new AtomicRef<>(null);
    // for elimination
    private final int SIZE = 64;
    private final int ITERS = 1000;
    private final int ATTEMPTS = 10;
    private final AtomicArray<Integer> values = new AtomicArray<>(SIZE);
    private final Random random = new Random();

    @Override
    public void push(int x) {
        // elimination loop
        for (int ind = random.nextInt(SIZE); ind < ATTEMPTS; ind = (ind + 1) % SIZE) {
            AtomicRef<Integer> ref = values.get(ind);
            Integer value = ref.getValue();
            if (value != null) {
                continue;
            }
            Integer newValue = x;
            if (ref.compareAndSet(value, newValue)) {
                for (int j = 0; j < ITERS; ++j) {
                    if (ref.getValue() != newValue) {
                        return;
                    }
                }
                if (!ref.compareAndSet(newValue, null)) {
                    return;
                }
                break;
            }
        }
        // default loop
        while (true) {
            Node curHead = head.getValue();
            Node newHead = new Node(x, curHead);
            if (head.compareAndSet(curHead, newHead)) {
                return;
            }
        }
    }

    @Override
    public int pop() {
        // elimination loop
        for (int ind = random.nextInt(SIZE); ind < ATTEMPTS; ind = (ind + 1) % SIZE) {
            AtomicRef<Integer> ref = values.get(ind);
            Integer value = ref.getValue();
            if (value != null && ref.compareAndSet(value, null)) {
                return value;
            }
        }
        // default loop
        while (true) {
            Node curHead = head.getValue();
            if (curHead == null) {
                return Integer.MIN_VALUE;
            }
            if (head.compareAndSet(curHead, curHead.next.getValue())) {
                return curHead.x;
            }
        }
    }
}
