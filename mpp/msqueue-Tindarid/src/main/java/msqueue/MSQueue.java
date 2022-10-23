package msqueue;

import kotlinx.atomicfu.AtomicRef;

public class MSQueue implements Queue {
    private AtomicRef<Node> head;
    private AtomicRef<Node> tail;

    public MSQueue() {
        Node dummy = new Node(0);
        this.head = new AtomicRef<>(dummy);
        this.tail = new AtomicRef<>(dummy);
    }

    @Override
    public void enqueue(int x) {
        Node newTail = new Node(x);
        while (true) {
            Node oldTail = tail.getValue();
            if (oldTail.next.compareAndSet(null, newTail)) {
                tail.compareAndSet(oldTail, newTail);
                return;
            } else {
                tail.compareAndSet(oldTail, oldTail.next.getValue());
            }
        }
    }

    @Override
    public int dequeue() {
        while (true) {
            Node oldHead = head.getValue();
            Node next = oldHead.next.getValue();
            Node oldTail = tail.getValue();
            if (oldHead == oldTail) {
                if (next == null) {
                    return Integer.MIN_VALUE;
                } else {
                    tail.compareAndSet(oldTail, next);
                }
            } else if (next != null) {
                int x = next.x;
                if (head.compareAndSet(oldHead, next)) {
                    return x;
                }
            }
        }
    }

    @Override
    public int peek() {
        while (true) {
            Node oldHead = head.getValue();
            Node next = oldHead.next.getValue();
            Node oldTail = tail.getValue();
            if (oldHead == oldTail) {
                if (next == null) {
                    return Integer.MIN_VALUE;
                } else {
                    tail.compareAndSet(oldTail, next);
                }
            } else if (next != null) {
                int x = next.x;
                if (head.getValue() == oldHead) {
                    return x;
                }
            }
        }
    }

    private class Node {
        final int x;
        AtomicRef<Node> next;

        Node(int x) {
            this.x = x;
            this.next = new AtomicRef<>(null);
        }
    }
}