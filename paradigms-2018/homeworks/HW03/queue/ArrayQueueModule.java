package queue;

import java.util.Arrays;

//INV:
// ((size == 0 && start == end) || (size > 0 && start != end)) && size < elements.length
// elements from start to end in the case of orded
public class ArrayQueueModule {
    private static int size;
    private static int start;
    private static int end;
    private static Object[] elements = new Object[5];

    //Pre: element != null
    //Post: 
    //      ((forall i = 0...elements.length - 1 : elements[i] == elements'[i]) || 
    //      (forall i = start, j = 0; i != end; i = getNextPos(i), j++ : elements'[j] == elements[i])) && 
    //      elements'.length == elements.length * 2 &&
    //      (end' == getNextPos(end) || end' == getNextPos(start' + size)) && 
    //      (start' == start || start == 0) && size' == size + 1
    //      elements[end] == element
    public static void enqueue(Object element) {
        assert element != null;

        ensureCapacity(size + 1);
        elements[end] = element;
        end = getNextPos(end);
        size++;
    }

    //Pre: 
    //Post: 
    //      ((forall i = 0...elements.length - 1 : elements[i] == elements'[i]) || 
    //      (forall i = start, j = 0; i != end; i = getNextPos(i), j++ : elements'[j] == elements[i])) && 
    //      elements'.length == elements.length * 2 &&
    //      (end' == end || end' == start' + size) && 
    //      (start' == start || start == 0) && size' == size
    private static void ensureCapacity(int capacity) {
        if (capacity < elements.length) {
            return;
        }
        int newCapacity = 2 * capacity;
        Object[] newElements = new Object[newCapacity];
        copy(elements, newElements, start, end, size);
        elements = newElements;
        start = 0;
        end = start + size;
    }

    //Pre: 0 <= pos < elements.length
    //Post: R = ((pos + 1) % elements.length) &&
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start == start' && end == end' && size == size'
    private static int getNextPos(int pos) {
        return (pos + 1) % elements.length;
    }

    //Pre: size > 0
    //Post: R = elements[start] &&
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start' == getNextPos(start) && end == end' && size' == size - 1
    public static Object dequeue() {
        assert size > 0;

        Object value = element();
        size--;
        start = getNextPos(start);
        return value;
    }

    //Pre: size > 0
    //Post: R = elements[start] && forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start == start' && end == end' && size == size'
    public static Object element() {
        assert size > 0;

        return elements[start];
    }

    //Pre: 
    //Post: R = size &&
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start == start' && end == end' && size == size'
    public static int size() {
        return size;
    }

    //Pre: 
    //Post: R = (size == 0) 
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start == start' && end == end' && size == size'
    public static boolean isEmpty() {
        return size == 0;
    }

    //Pre: 
    //Post: R = instance of ArrayQueue && 
    //      R.start == start && R.end == end && R.size == size && R.elements.length == elements.length && 
    //      forall i = 0...elements.length - 1 : elements[i] == R.elements[i] 
    //
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start == start' && end == end' && size == size'
    public static ArrayQueueModule makeCopy() {
        final ArrayQueueModule copy = new ArrayQueueModule();
        copy.size = size;
        copy.elements = Arrays.copyOf(elements, size);
        copy.start = start;
        copy.end = end;
        return copy;
    }

    //Pre: 
    //Post: 
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start' == 0 && end == start' && size == 0
    public static void clear() {
        start = 0;
        end = start;
        size = 0;
    }


    //Pre: 
    //Post: R = Object[size] && for i = start, j = 0; i != end; i = getNextPos(i), j++ : res[j] == elements[i]
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start == start' && end == end' && size == size'
    public static Object[] toArray() {
        Object[] res = new Object[size];
        copy(elements, res, start, end, size);
        return res;
    }


    private static void copy(Object[] src, Object[] dest, int start, int end, int size) {
        if (start > end) {
            System.arraycopy(src, start, dest, 0, src.length - start);
            System.arraycopy(src, 0, dest, src.length - start, end);
        } else {
            System.arraycopy(src, start, dest, 0, size);
        }
    }
}
