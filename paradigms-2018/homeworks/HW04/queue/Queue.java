package queue;

public interface Queue {
    public void enqueue(Object element);
    public Object element();
    public Object dequeue();
    public void clear();
    public int size();
    public boolean isEmpty();
    public Object[] toArray();
    public Queue makeCopy();
}
