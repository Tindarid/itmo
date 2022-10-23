package expression;

import expression.exceptions.EvaluationException;
import expression.type.Type;

public abstract class BinaryOperation<T extends Number> implements TripleExpression<T> {
    protected TripleExpression<T> firstOperand;
    protected TripleExpression<T> secondOperand;

    public BinaryOperation(TripleExpression<T> first, TripleExpression<T> second) {
        firstOperand = first;
        secondOperand = second;
    }

    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) throws EvaluationException {
        return calc(firstOperand.evaluate(x, y, z), secondOperand.evaluate(x, y, z));
    }

    protected abstract Type<T> calc(Type<T> a, Type<T> b) throws EvaluationException;
}
