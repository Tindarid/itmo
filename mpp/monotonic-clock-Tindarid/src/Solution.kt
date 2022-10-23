/**
 * В теле класса решения разрешено использовать только переменные делегированные в класс RegularInt.
 * Нельзя volatile, нельзя другие типы, нельзя блокировки, нельзя лазить в глобальные переменные.
 */
class Solution : MonotonicClock {
    private var c1d1 by RegularInt(0)
    private var c1d2 by RegularInt(0)
    private var r by RegularInt(0)
    private var c2d1 by RegularInt(0)
    private var c2d2 by RegularInt(0)

    override fun write(time: Time) {
        // write left-to-right (c2)
        c2d1 = time.d1
        c2d2 = time.d2
        // write the right one
        r = time.d3
        // write right-to-left (c1)
        c1d2 = c2d2
        c1d1 = c2d1
    }

    override fun read(): Time {
        // read left-to-right (r1)
        val r1d1 = c1d1
        val r1d2 = c1d2
        // read the right one
        val w = r
        // read left-to-right (r2)
        val r2d2 = c2d2
        val r2d1 = c2d1
        // resolve
        return if (r1d1 == r2d1) {
            if (r1d2 == r2d2) {
                Time(r2d1, r2d2, w)
            } else {
                Time(r2d1, r2d2, 0)
            }
        } else {
            Time(r2d1, 0, 0)
        }
    }
}