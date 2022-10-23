package expression;

import expression.exceptions.*;

public class CheckedSubtract extends BinaryOperation {
    public CheckedSubtract(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    public int calc(int a, int b) throws OverflowException {
        if ((Integer.MAX_VALUE + b < a && b < 0) || (Integer.MIN_VALUE + b > a && b > 0)) {
            throw new OverflowException("Overflow.");
        } 
        return a - b;
    }
}
