package expression;

import expression.exceptions.*;

public class CheckedDivide extends BinaryOperation {
    public CheckedDivide(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    public int calc(int a, int b) throws EvaluationException {
        if (b == 0) {
            throw new OverflowException("Division by zero.");
        }
        if (a == Integer.MIN_VALUE && b == -1) {
            throw new OverflowException("Overflow.");
        }
        return a / b;
    }
}
