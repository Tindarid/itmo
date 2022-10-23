import java.lang.ThreadLocal

class Solution : AtomicCounter {
    private val last = ThreadLocal<Node>()
    private val root = Node(0)

    override fun getAndAdd(x: Int): Int {
        while (true) {
            if (last.get() == null) {
                last.set(root);
            }
            val n = last.get()
            val old = n.value
            val node = Node(old + x)
            val next = n.next.decide(node)
            last.set(next);
            if (next == node) {
                return old
            }
        }
    }

    private class Node(val value : Int) {
        val next = Consensus<Node>()
    }
}
