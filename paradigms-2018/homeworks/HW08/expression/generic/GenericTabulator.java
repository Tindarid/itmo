package expression.generic;

import expression.*;
import expression.parser.*;
import expression.exceptions.*;
import expression.type.*;
import java.math.BigInteger;

public class GenericTabulator implements Tabulator {
    public Object[][][] tabulate(String mode, String expression, int x1, int x2, int y1, int y2, int z1, int z2) throws Exception {
        if (mode.equals("i")) {
            return (new Executor<Integer>()).execute(expression, new SafeIntType("0"), x1, x2, y1, y2, z1, z2);
        } else if (mode.equals("d")) {
            return (new Executor<Double>()).execute(expression, new DoubleType("0"), x1, x2, y1, y2, z1, z2);
        } else if (mode.equals("bi")) {
            return (new Executor<BigInteger>()).execute(expression, new BigIntType("0"), x1, x2, y1, y2, z1, z2);
        } else if (mode.equals("s")) {
            return (new Executor<Short>()).execute(expression, new UnsafeShortType("0"), x1, x2, y1, y2, z1, z2);
        } else if (mode.equals("u")) {
            return (new Executor<Integer>()).execute(expression, new UnsafeIntType("0"), x1, x2, y1, y2, z1, z2);
        } else if (mode.equals("l")) {
            return (new Executor<Long>()).execute(expression, new UnsafeLongType("0"), x1, x2, y1, y2, z1, z2);
        } else {
            return null;
        }
    }
}
