import java.util.concurrent.atomic.*
import kotlin.coroutines.*

private class SegmentQueue<T> {
    private val NODE_SIZE = 2
    private val DONE = Any()
    private val head = AtomicReference<Node>()
    private val tail = AtomicReference<Node>()

    init {
        val node = Node(null)
        head.set(node)
        tail.set(node)
    }

    fun enqueue(x: T) {
        while (true) {
            val last = tail.get()
            val enqIdx = last.enqIdx.getAndIncrement()
            if (enqIdx >= NODE_SIZE) {
                val newLast = Node(x)
                if (last.next.compareAndSet(null, newLast)) {
                    tail.compareAndSet(last, newLast)
                    break
                } else {
                    tail.compareAndSet(last, last.next.get())
                }
            } else if (last.data.compareAndSet(enqIdx, null, x)) break
        }
    }

    fun dequeue(): T {
        while (true) {
            val first = head.get()
            val next = first.next.get()
            if (first.isEmpty() && next != null) {
                head.compareAndSet(first, next)
            } else {
                val deqIdx = first.deqIdx.getAndIncrement()
                if (deqIdx >= NODE_SIZE) continue
                val res = first.data.getAndSet(deqIdx, DONE) ?: continue
                return res as T
            }
        }
    }

    private inner class Node(x: Any?) {
        val next = AtomicReference<Node>(null)
        val enqIdx = AtomicInteger(0)
        val deqIdx = AtomicInteger(0)
        val data = AtomicReferenceArray<Any>(NODE_SIZE)

        init {
            if (x != null) {
                data.set(0, x)
                enqIdx.set(1)
            }
        }

        fun isEmpty(): Boolean {
            val deqIdx = deqIdx.get()
            val enqIdx = enqIdx.get()
            return deqIdx >= enqIdx || deqIdx >= NODE_SIZE
        }
    }
}

class BlockingStackImpl<E> : BlockingStack<E> {

    // ==========================
    // Segment Queue Synchronizer
    // ==========================

    private val queue = SegmentQueue<Continuation<E>>()

    private suspend fun suspend(): E {
        return suspendCoroutine { cont -> queue.enqueue(cont) }
    }

    private fun resume(element: E) {
        queue.dequeue().resume(element)
    }

    // ==============
    // Blocking Stack
    // ==============


    private val head = AtomicReference<Node<E?>?>()
    private val elements = AtomicInteger()

    override fun push(element: E) {
        val elements = this.elements.getAndIncrement()
        if (elements >= 0) {
            // push the element to the top of the stack
            while (true) {
                val first = head.get()
                if (first != null && first.element == SUSPENDED) {
                    val cont = first.cont
                    if (head.compareAndSet(first, first.next)) {
                        cont?.resume(element)
                        break
                    }
                } else {
                    val node = Node(element, first, null)
                    if (head.compareAndSet(first, node)) return
                }
            }
        } else {
            // resume the next waiting receiver
            resume(element)
        }
    }

    override suspend fun pop(): E {
        val elements = this.elements.getAndDecrement()
        if (elements > 0) {
            // remove the top element from the stack
            while (true) {
                val first = head.get()
                if (first == null || first.element == SUSPENDED) {
                    val result = suspendCoroutine<E?> { cont ->
                        val node = Node(SUSPENDED, first, cont)
                        if (!head.compareAndSet(first, node)) {
                            cont.resume(null)
                        }
                    }
                    if (result != null) return result
                } else if (head.compareAndSet(first, first.next)) {
                    return first.element as E
                }
            }
        } else {
            return suspend()
        }
    }
}

private class Node<E>(val element: Any?, val next: Node<E>?, val cont: Continuation<E>?)

private val SUSPENDED = Any()