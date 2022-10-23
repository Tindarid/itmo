package expression;

import expression.exceptions.EvaluationException;
import expression.type.Type;

public class CheckedMultiply<T extends Number> extends BinaryOperation<T> {
    public CheckedMultiply(TripleExpression<T> first, TripleExpression<T> second) {
        super(first, second);
    }

    public Type<T> calc(Type<T> a, Type<T> b) throws EvaluationException {
        return a.mul(b);
    }
}
