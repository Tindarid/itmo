package queue;

import java.util.Arrays;

//INV:
// ((q.size == 0 && q.start == q.end) || (q.size > 0 && q.start != q.end)) && q.size < q.elements.length
// elements from start to end in the case of orded
public class ArrayQueueADT {
    private int size;
    private int start;
    private int end;
    private Object[] elements = new Object[5];

    //Pre: element != null
    //Post: 
    //      ((forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i]) || 
    //      (forall i = q.start, j = 0; i != q.end; i = getNextPos(q, i), j++ : q.elements'[j] == q.elements[i])) && 
    //      q.elements'.length == q.elements.length * 2 &&
    //      (q.end' == getNextPos(q, q.end) || q.end' == getNextPos(q, q.start' + q.size)) && 
    //      (q.start' == q.start || q.start == 0) && q.size' == q.size + 1
    //      q.elements[end] == q.element
    public static void enqueue(ArrayQueueADT q, Object element) {
        assert element != null;

        ensureCapacity(q, q.size + 1);
        q.elements[q.end] = element;
        q.end = getNextPos(q, q.end);
        q.size++;
    }

    //Pre: 
    //Post: 
    //      ((forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i]) || 
    //      (forall i = q.start, j = 0; i != q.end; i = getNextPos(q, i), j++ : q.elements'[j] == q.elements[i])) && 
    //      q.elements'.length == q.elements.length * 2 &&
    //      (q.end' == q.end || q.end' == q.start' + q.size) && 
    //      (q.start' == q.start || q.start == 0) && q.size' == q.size
    private static void ensureCapacity(ArrayQueueADT q, int capacity) {
        if (capacity < q.elements.length) {
            return;
        }
        int newCapacity = 2 * capacity;
        Object[] newElements = new Object[newCapacity];
        copy(q.elements, newElements, q.start, q.end, q.size);
        q.elements = newElements;
        q.start = 0;
        q.end = q.start + q.size;
    }

    //Pre: 0 <= pos < q.elements.length
    //Post: R = ((pos + 1) % q.elements.length) &&
    //      forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i] &&
    //      q.start == q.start' && q.end == q.end' && q.size == q.size'
    private static int getNextPos(ArrayQueueADT q, int pos) {
        return (pos + 1) % q.elements.length;
    }

    //Pre: q.size > 0
    //Post: R = q.elements[q.start] &&
    //      forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i] &&
    //      q.start == q.start' && q.end == q.end' && q.size == q.size' - 1
    public static Object dequeue(ArrayQueueADT q) {
        assert q.size > 0;

        Object value = element(q);
        q.size--;
        q.start = getNextPos(q, q.start);
        return value;
    }

    //Pre: q.size > 0
    //Post: R = q.elements[q.start] && forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i] &&
    //      q.start == q.start' && q.end == q.end' && q.size == q.size'
    public static Object element(ArrayQueueADT q) {
        assert q.size > 0;

        return q.elements[q.start];
    }

    //Pre: 
    //Post: R = q.size &&
    //      forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i] &&
    //      q.start == q.start' && q.end == q.end' && q.size == q.size'
    public static int size(ArrayQueueADT q) {
        return q.size;
    }

    //Pre: 
    //Post: R = (q.size == 0) 
    //      forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i] &&
    //      q.start == q.start' && q.end == q.end' && q.size == q.size'
    public static boolean isEmpty(ArrayQueueADT q) {
        return q.size == 0;
    }

    //Pre: 
    //Post: R = instance of ArrayQueueADT && 
    //      R.start == q.start && R.end == q.end && R.size == q.size && R.elements.length == q.elements.length && 
    //      forall i = 0...q.elements.length - 1 : q.elements[i] == R.elements[i] 
    //
    //      forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i] &&
    //      q.start == q.start' && q.end == q.end' && q.size == q.size'
    public static ArrayQueueADT makeCopy(ArrayQueueADT q) {
        final ArrayQueueADT copy = new ArrayQueueADT();
        copy.size = q.size;
        copy.elements = Arrays.copyOf(q.elements, q.size);
        copy.start = q.start;
        copy.end = q.end;
        return copy;
    }

    //Pre: 
    //Post: 
    //      forall i = 0...elements.length - 1 : elements[i] == elements'[i] &&
    //      start' == 0 && end' == start && size == 0
    public static void clear(ArrayQueueADT q) {
        q.start = 0;
        q.end = q.start;
        q.size = 0;
    }


    //Pre: 
    //Post: R = Object[size] && for i = q.start, j = 0; i != q.end; i = getNextPos(q, i), j++ : res[j] == q.elements[i]
    //      forall i = 0...q.elements.length - 1 : q.elements[i] == q.elements'[i] &&
    //      q.start == q.start' && q.end == q.end' && q.size == q.size'
    public static Object[] toArray(ArrayQueueADT q) {
        Object[] res = new Object[q.size];
        copy(q.elements, res, q.start, q.end, q.size);
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
