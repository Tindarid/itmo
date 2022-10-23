package dijkstra

import java.util.*
import java.util.concurrent.Phaser
import java.util.concurrent.atomic.AtomicInteger
import java.util.concurrent.locks.ReentrantLock
import kotlin.Comparator
import kotlin.concurrent.thread

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> o1!!.distance.compareTo(o2!!.distance) }

class MultiQueue(workers : Int, private val comparator : Comparator<Node>) {
    private val size = 2 * workers
    private val queues = Array(size) { Pair(ReentrantLock(), PriorityQueue(comparator)) }
    private val random = Random()

    fun add(node: Node) {
        while (true) {
            val r = random.nextInt(size)
            val (l, q) = queues[r]
            if (l.tryLock()) {
                try {
                    q.add(node);
                    break;
                } finally {
                    l.unlock();
                }
            }
        }
    }

    fun poll(): Node? {
        while (true) {
            var r1 = random.nextInt(size)
            var r2 = (r1 + random.nextInt(size - 1) + 1) % size
            if (r1 > r2) {
                val temp = r1
                r1 = r2
                r2 = temp
            }
            val (l1, q1) = queues[r1]
            if (l1.tryLock()) {
                try {
                    val (l2, q2) = queues[r2]
                    if (l2.tryLock()) {
                        try {
                            val n1 = q1.peek()
                            val n2 = q2.peek()
                            return if (n1 == null && n2 == null) {
                                null;
                            } else if (n1 == null) {
                                q2.poll()
                            } else if (n2 == null) {
                                q1.poll()
                            } else if (comparator.compare(n1, n2) >= 0) {
                                q2.poll()
                            } else {
                                q1.poll()
                            }
                        } finally {
                            l2.unlock();
                        }
                    }
                } finally {
                    l1.unlock();
                }
            }
        }
    }
}

// Returns `Integer.MAX_VALUE` if a path has not been found.
fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    // The distance to the start node is `0`
    start.distance = 0
    // Create a priority (by distance) queue and add the start node into it
    val q = MultiQueue(workers, NODE_DISTANCE_COMPARATOR)
    val activeNodes = AtomicInteger(1)
    q.add(start)
    // Run worker threads and wait until the total work is done
    val onFinish = Phaser(workers + 1) // `arrive()` should be invoked at the end by each worker
    repeat(workers) {
        thread {
            while (true) {
                val cur: Node = q.poll() ?: if (activeNodes.get() == 0) break else continue
                val curDistance = cur.distance
                for (e in cur.outgoingEdges) {
                    while (true) {
                        val edgeDistance = e.to.distance
                        if (edgeDistance > curDistance + e.weight) {
                            if (e.to.casDistance(edgeDistance, curDistance + e.weight)) {
                                q.add(e.to)
                                activeNodes.incrementAndGet()
                            } else {
                                continue;
                            }
                        }
                        break;
                    }
                }
                activeNodes.decrementAndGet()
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}