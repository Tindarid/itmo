import java.util.concurrent.atomic.AtomicReference;
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class SynchronousQueueMS<E> : SynchronousQueue<E> {
    var head : AtomicReference<Node>
    var tail : AtomicReference<Node>

    open inner class Node { val next = AtomicReference<Node>(null) }
    inner class ReceiverNode(val c : Continuation<E>) : Node()
    inner class SenderNode(val c : Continuation<Unit>, val e : E) : Node()

    init {
        val dummy = Node()
        head = AtomicReference(dummy)
        tail = AtomicReference(dummy)
    }

    override suspend fun send(element: E) {
        while (true) {
            val t = tail.get()
            val h = head.get()
            if (h == t || t !is ReceiverNode) {
                val res = suspendCoroutine<Unit?> { cont ->
                    val node = SenderNode(cont, element)
                    if (t.next.compareAndSet(null, node)) {
                        tail.compareAndSet(t, node)
                    } else {
                        tail.compareAndSet(t, t.next.get())
                        cont.resume(null)
                    }
                }
                if (res == null) continue else return
            } else {
                val n = h.next.get() ?: continue
                if (n !is ReceiverNode) continue
                if (head.compareAndSet(h, n)) {
                    n.c.resume(element)
                    return
                }
            }
        }
    }

    override suspend fun receive(): E {
        while (true) {
            val t = tail.get()
            val h = head.get()
            if (h == t || t !is SenderNode) {
                val res = suspendCoroutine<E?> { cont ->
                    val node = ReceiverNode(cont)
                    if (t.next.compareAndSet(null, node)) {
                        tail.compareAndSet(t, node)
                    } else {
                        tail.compareAndSet(t, t.next.get())
                        cont.resume(null)
                    }
                }
                if (res == null) continue else return res
            } else {
                val n = h.next.get() ?: continue
                if (n !is SenderNode) continue
                if (head.compareAndSet(h, n)) {
                    n.c.resume(Unit)
                    return n.e
                }
            }
        }
    }
}
