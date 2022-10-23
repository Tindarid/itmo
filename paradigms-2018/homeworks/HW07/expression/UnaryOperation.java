package expression;

import expression.exceptions.*;

public abstract class UnaryOperation implements CommonExpression {
    protected CommonExpression operand;

    public UnaryOperation(CommonExpression expr) {
        operand = expr;
    }

    public int evaluate(int x, int y, int z) throws EvaluationException {
        return calc(operand.evaluate(x, y, z));
    }

    protected abstract int calc(int a) throws EvaluationException;
}
