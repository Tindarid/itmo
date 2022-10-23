package expression;

import expression.exceptions.EvaluationException;
import expression.type.Type;

public class CheckedNegate<T extends Number> extends UnaryOperation<T> {
    public CheckedNegate(TripleExpression<T> temp) {
        super(temp);
    }

    public Type<T> calc(Type<T> a) throws EvaluationException {
        return a.neg();
    }
}
