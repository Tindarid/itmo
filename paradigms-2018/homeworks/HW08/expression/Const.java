package expression;

import expression.exceptions.EvaluationException;
import expression.type.Type;

public class Const<T extends Number> implements TripleExpression<T> {
    private Type<T> value;

    public Const(Type<T> v) {
        value = v;
    }

    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) throws EvaluationException {
        return value;
    }
}
