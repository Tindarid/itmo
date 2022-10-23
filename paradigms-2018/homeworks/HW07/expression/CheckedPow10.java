package expression;

import expression.exceptions.*;

public class CheckedPow10 extends UnaryOperation {
    public CheckedPow10(CommonExpression temp) {
        super(temp);
    }

    public int calc(int a) throws OverflowException {
        int ans = 1;
        if (a > 9 || a < 0) {
            throw new OverflowException("Overflow.");
        }
        for (int i = 0; i < a; i++) {
            ans *= 10;
        }
        return ans;
    }
}
