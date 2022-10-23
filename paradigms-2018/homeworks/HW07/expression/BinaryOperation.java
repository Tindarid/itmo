package expression;

import expression.exceptions.*;

public abstract class BinaryOperation implements CommonExpression {
    protected CommonExpression firstOperand;
    protected CommonExpression secondOperand;

    public BinaryOperation(CommonExpression first, CommonExpression second) {
        firstOperand = first;
        secondOperand = second;
    }

    public int evaluate(int x, int y, int z) throws EvaluationException {
        return calc(firstOperand.evaluate(x, y, z), secondOperand.evaluate(x, y, z));
    }

    protected abstract int calc(int a, int b) throws EvaluationException;
}
