package expression;

import expression.exceptions.*;

public class Variable implements CommonExpression {
    private String var;

    public Variable(String v) {
        var = v;
    }

    public int evaluate(int x, int y, int z) throws EvaluationException {
        if (var.equals("x")) {
            return x;
        } else if (var.equals("y")) {
            return y;
        } else if (var.equals("z")) {
            return z;
        } else {
            return 0;
        }
    }
}
