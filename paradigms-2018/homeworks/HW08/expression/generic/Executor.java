package expression.generic;

import expression.*;
import expression.parser.*;
import expression.exceptions.*;
import expression.type.*;
import java.math.BigInteger;

public class Executor<T extends Number> {
    public Object[][][] execute(String expression, Type<T> m, int x1, int x2, int y1, int y2, int z1, int z2) throws ExpressionException {
        Object[][][] res = new Object[x2 - x1 + 1][y2 - y1 + 1][z2 - z1 + 1];
        ExpressionParser<T> parser = new ExpressionParser<T>();
        TripleExpression<T> expr = parser.parse(expression, m);
        int dX = x2 - x1;
        int dY = y2 - y1;
        int dZ = z2 - z1;
        for (int i = 0; i <= dX; i++) {
            for (int j = 0; j <= dY; j++) {
                for (int k = 0; k <= dZ; k++) {
                    try {
                        Type<T> x = m.parse((i + x1));
                        Type<T> z = m.parse((k + z1));
                        Type<T> y = m.parse((j + y1));
                        res[i][j][k] = expr.evaluate(x, y, z).value();
                    } catch (Exception e) {
                        res[i][j][k] = null;
                    }
                }
            }
        }
        return res;

    }
}
