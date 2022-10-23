package expression;

import expression.exceptions.EvaluationException;
import expression.type.Type;

public class CheckedAdd<T extends Number> extends BinaryOperation<T> {
    public CheckedAdd(TripleExpression<T> first, TripleExpression<T> second) {
        super(first, second);
    }

    public Type<T> calc(Type<T> a, Type<T> b) throws EvaluationException {
        return a.add(b);
    }
}
