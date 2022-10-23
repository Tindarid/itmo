package expression;

import expression.exceptions.*;

public class Const implements CommonExpression {
    private int value;

    public Const(int v) {
        value = v;
    }

    public int evaluate(int x, int y, int z) throws EvaluationException {
        return value;
    }
}
