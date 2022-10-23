package expression;

import expression.exceptions.EvaluationException;
import expression.type.Type;

public abstract class UnaryOperation<T extends Number> implements TripleExpression<T> {
    protected TripleExpression<T> operand;

    public UnaryOperation(TripleExpression<T> expr) {
        operand = expr;
    }

    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) throws EvaluationException {
        return calc(operand.evaluate(x, y, z));
    }

    protected abstract Type<T> calc(Type<T> a) throws EvaluationException;
}
