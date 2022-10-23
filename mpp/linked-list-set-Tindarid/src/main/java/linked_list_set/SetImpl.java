package linked_list_set;

import kotlinx.atomicfu.AtomicRef;

public class SetImpl implements Set {
    private class Node {
        AtomicRef<Node> nr;
        int x;

        Node() { }
        Node(int x, Node nr) {
            this.nr = new AtomicRef<>(nr);
            this.x = x;
        }
    }

    private class Removed extends Node {
        final Node node;

        Removed(Node node) {
            this.node = node;
            this.nr = node.nr;
            this.x = node.x;
        }
    }

    private class Window {
        Node cur, next;
    }

    private final AtomicRef<Node> head = new AtomicRef<>(new Node(Integer.MIN_VALUE,
            new Node(Integer.MAX_VALUE, null)));

    /**
     * Returns the {@link Window}, where cur.x < x <= next.x
     */
    private Window findWindow(int x) {
        retry: while (true) {
            Window w = new Window();
            w.cur = head.getValue();
            w.next = w.cur.nr.getValue();
            while (w.next.x < x) {
                Node node = w.next.nr.getValue();
                if (node instanceof Removed) {
                    if (!w.cur.nr.compareAndSet(getInner(w.next), getInner(node))) {
                        continue retry;
                    }
                } else {
                    w.cur = w.next;
                }
                w.next = w.cur.nr.getValue();
            }
            Node node = w.next.nr.getValue();
            if (node instanceof Removed) {
                w.cur.nr.compareAndSet(w.next, getInner(node));
                continue;
            }
            return w;
        }
    }

    @Override
    public boolean add(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.next.x == x) {
                return false;
            }
            w.next = getInner(w.next);
            Node node = new Node(x, w.next);
            if (w.cur.nr.compareAndSet(w.next, node)) {
                return true;
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Window w = findWindow(x);
            if (w.next.x != x) {
                return false;
            }
            Node node = getInner(w.next.nr.getValue());
            if (w.next.nr.compareAndSet(node, new Removed(node))) {
                w.cur.nr.compareAndSet(getInner(w.next), node);
                return true;
            }
        }
    }

    @Override
    public boolean contains(int x) {
        Window w = findWindow(x);
        return w.next.x == x;
    }

    private Node getInner(Node node) {
        if (node instanceof Removed) {
            node = ((Removed)node).node;
        }
        return node;
    }
}