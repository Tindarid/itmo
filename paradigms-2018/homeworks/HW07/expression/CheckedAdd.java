package expression;

import expression.exceptions.*;

public class CheckedAdd extends BinaryOperation {
    public CheckedAdd(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    public int calc(int a, int b) throws OverflowException {
        if ((Integer.MAX_VALUE - a < b && a > 0) || (Integer.MIN_VALUE - a > b && a < 0)) {
            throw new OverflowException("Overflow.");
        } 
        return a + b;
    }
}
