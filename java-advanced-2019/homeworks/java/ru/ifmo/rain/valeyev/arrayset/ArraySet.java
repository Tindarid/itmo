package ru.ifmo.rain.valeyev.arrayset;

import java.util.*;

public class ArraySet<T> extends AbstractSet<T> implements NavigableSet<T> {
    private class ReversedList<T> extends AbstractList<T> implements List<T> {
        private final List<T> content;

        public ReversedList(List<T> list) {
            content = list;
        }

        public T get(int ind) {
            return content.get(content.size() - ind - 1);
        }

        public int size() {
            return content.size();
        }

        public List<T> getContent() {
            return content;
        }
    }

    private final Comparator<? super T> comp;
    private final List<T> content;

    public ArraySet() {
        this.comp = null;
        content = Collections.emptyList();
    }

    public ArraySet(Comparator<? super T> comp) {
        this.comp = comp;
        content = Collections.emptyList();
    }

    public ArraySet(Collection<? extends T> coll) {
        this.comp = null;
        content = new ArrayList<>(new TreeSet<>(coll));
    }

    public ArraySet(Collection<? extends T> coll, Comparator<? super T> comp) {
        this.comp = comp;
        TreeSet temp = new TreeSet<>(comp);
        temp.addAll(coll);
        content = new ArrayList<>(temp);
    }

    private ArraySet(List<T> list, Comparator<? super T> comp) {
        this.comp = comp;
        this.content = list;
    }

    public Comparator<? super T> comparator() {
        return comp;
    }

    public int size() {
        return content.size();
    }

    public boolean contains(Object obj) {
        return Collections.binarySearch(content, (T) obj, comp) >= 0;
    }

    private T getElement(int index) {
        return index >= 0 ? content.get(index) : null;
    }

    private int getIndex(T element, int shiftSuccess, int shiftFail) {
        int index = Collections.binarySearch(content, element, comp);
        index = index < 0 ? -index - 1 + shiftFail : index + shiftSuccess;
        return index >= 0 && index < size() ? index : -1;
    }

    public T last() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        return getElement(size() - 1);
    }

    public T first() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        return getElement(0);
    }

    public NavigableSet<T> subSet(T fromElement, boolean fromInclusive, T toElement, boolean toInclusive) {
        int l = fromInclusive ? ceilingInd(fromElement) : higherInd(fromElement);
        int r = toInclusive ? floorInd(toElement) : lowerInd(toElement);
        return l == -1 || r == -1 || l > r ? new ArraySet<>(comp) : new ArraySet<>(content.subList(l, r + 1), comp);
    }

    public NavigableSet<T> headSet(T toElement, boolean inclusive) {
        return isEmpty() ? new ArraySet<>(comp) : subSet(first(), true, toElement, inclusive);
    }

    public NavigableSet<T> tailSet(T fromElement, boolean inclusive) {
        return isEmpty() ? new ArraySet<>(comp) : subSet(fromElement, inclusive, last(), true);
    }

    public SortedSet<T> subSet(T fromElement, T toElement) {
        if (comp != null) {
            if (comp.compare(fromElement, toElement) > 0) {
                throw new IllegalArgumentException("Not allowed borders");
            }
        } else {
            if (fromElement instanceof Comparable && toElement instanceof Comparable) {
                if (((Comparable) fromElement).compareTo((Comparable) toElement) > 0) {
                    throw new IllegalArgumentException("Not allowed borders");
                }
            }
        }
        return subSet(fromElement, true, toElement, false);
    }

    public SortedSet<T> headSet(T toElement) {
        return headSet(toElement, false);
    }

    public SortedSet<T> tailSet(T fromElement) {
        return tailSet(fromElement, true);
    }

    public NavigableSet<T> descendingSet() {
        List<T> list = this.content;
        if (list instanceof ReversedList) {
            list = ((ReversedList) list).getContent();
        } else {
            list = new ReversedList<T>(list);
        }
        return new ArraySet<>(list, Collections.reverseOrder(comp));
    }

    public T pollFirst() {
        throw new UnsupportedOperationException();
    }

    public T pollLast() {
        throw new UnsupportedOperationException();
    }

    public int higherInd(T element) {
        return getIndex(element, 1, 0);
    }

    public int ceilingInd(T element) {
        return getIndex(element, 0, 0);
    }

    public int lowerInd(T element) {
        return getIndex(element, -1, -1);
    }

    public int floorInd(T element) {
        return getIndex(element, 0, -1);
    }

    public T higher(T element) {
        return getElement(higherInd(element));
    }

    public T ceiling(T element) {
        return getElement(ceilingInd(element));
    }

    public T lower(T element) {
        return getElement(lowerInd(element));
    }

    public T floor(T element) {
        return getElement(floorInd(element));
    }

    public Iterator<T> iterator() {
        return Collections.unmodifiableList(content).iterator();
    }

    public Iterator<T> descendingIterator() {
        return descendingSet().iterator();
    }
}
