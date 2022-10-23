package expression;

import expression.exceptions.*;

public class CheckedNegate extends UnaryOperation {
    public CheckedNegate(CommonExpression temp) {
        super(temp);
    }

    public int calc(int a) throws OverflowException {
        if (a == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow.");
        }
        return -a;
    }
}
