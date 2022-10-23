package expression;

import expression.exceptions.*;

public class CheckedLog10 extends UnaryOperation {
    public CheckedLog10(CommonExpression temp) {
        super(temp);
    }

    public int calc(int a) throws EvaluationException {
        if (a <= 0) {
            throw new IllegalOperationException("Log10 of negative number.");
        }
        //return Integer.toString(a).length() - 1;
        int ans = 0;
        while (a != 0) {
            a /= 10;
            ans++;
        }
        return ans - 1;
    }
}
