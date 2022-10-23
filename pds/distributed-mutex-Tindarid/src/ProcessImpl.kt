package mutex

/**
 * Distributed mutual exclusion implementation.
 * All functions are called from the single main thread.
 *
 * @author Nursan Valeyev
 */
class ProcessImpl(private val env: Environment) : Process {
    private var status = Status.WAIT
    private val forks = Array(env.nProcesses + 1) { Fork() }

    init {
        val id = env.processId
        for (i in 1..env.nProcesses) {
            forks[i].own = id >= i
        }
    }

    private fun sendFork(id: Int) {
        forks[id] = Fork()
        env.send(id) { writeEnum(MsgType.FORK) }
    }

    private fun checkCSEnter(firstly: Boolean) {
        var hasAllForks = true
        for (i in 1..env.nProcesses) {
            if (!forks[i].own) {
                if (firstly) {
                    env.send(i) { writeEnum(MsgType.REQ_FORK) }
                }
                hasAllForks = false
            }
        }
        if (hasAllForks) {
            status = Status.CS
            env.locked()
        }
    }

    override fun onMessage(srcId: Int, message: Message) {
        val msgType = message.parse { readEnum<MsgType>() }
        when (msgType) {
            MsgType.FORK -> {
                check(!forks[srcId].own)
                forks[srcId].own = true
                forks[srcId].clean = true
                forks[srcId].pending = false
                if (status == Status.REQ) {
                    checkCSEnter(false)
                }
            }
            MsgType.REQ_FORK -> {
                check(forks[srcId].own)
                when (status) {
                    Status.CS -> forks[srcId].pending = true
                    Status.WAIT -> sendFork(srcId)
                    Status.REQ -> {
                        if (!forks[srcId].clean) {
                            sendFork(srcId)
                            env.send(srcId) { writeEnum(MsgType.REQ_FORK) }
                        } else {
                            forks[srcId].pending = true
                        }
                    }
                }
            }
        }
    }

    override fun onLockRequest() {
        check(status == Status.WAIT)
        status = Status.REQ
        checkCSEnter(true)
    }

    override fun onUnlockRequest() {
        check(status == Status.CS)
        status = Status.WAIT
        env.unlocked()

        for (i in 1..env.nProcesses) {
            check(forks[i].own)
            forks[i].clean = false
            if (forks[i].pending) {
                forks[i] = Fork()
                env.send(i) { writeEnum(MsgType.FORK) }
            }
        }
    }

    enum class MsgType { FORK, REQ_FORK }
    enum class Status  { WAIT, REQ, CS }

    class Fork {
        var own = false
        var pending = false
        var clean = true
    }
}
