package expression;

import expression.exceptions.*;

public class CheckedMultiply extends BinaryOperation {
    public CheckedMultiply(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    public int calc(int a, int b) throws OverflowException {
        if (a > 0 && b > 0 && Integer.MAX_VALUE / a < b) {
            throw new OverflowException("Overflow.");
        }
        if (a > 0 && b < 0 && Integer.MIN_VALUE / a > b) {
            throw new OverflowException("Overflow.");
        }
        if (a < 0 && b > 0 && Integer.MIN_VALUE / b > a) {
            throw new OverflowException("Overflow.");
        }
        if (a < 0 && b < 0 && Integer.MAX_VALUE / a > b) {
            throw new OverflowException("Overflow.");
        }
        return a * b;
    }
}
