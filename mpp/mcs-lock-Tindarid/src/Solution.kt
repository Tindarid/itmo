import java.util.concurrent.atomic.*

class Solution(val env: Environment) : Lock<Solution.Node> {
    val tail = AtomicReference<Node>()

    override fun lock(): Node {
        val node = Node()
        val pred = tail.getAndSet(node)
        if (pred != null) {
            pred.next.value = node
            while (node.locked.value) env.park()
        }
        return node
    }

    override fun unlock(node: Node) {
        val next = node.next
        if (next.value == null) {
            if (tail.compareAndSet(node, null)) return
            while (next.value == null) continue
        }
        next.value.locked.value = false
        env.unpark(next.value.thread)
    }

    class Node {
        val thread = Thread.currentThread()
        val locked = AtomicReference<Boolean>(true)
        val next   = AtomicReference<Node>()
    }
}