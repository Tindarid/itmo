package expression;

import expression.exceptions.EvaluationException;
import expression.type.Type;

public class Variable<T extends Number> implements TripleExpression<T> {
    private String var;

    public Variable(String v) {
        var = v;
    }

    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) throws EvaluationException {
        if (var.equals("x")) {
            return x;
        } else if (var.equals("y")) {
            return y;
        } else if (var.equals("z")) {
            return z;
        } else {
            return null;
        }
    }
}
