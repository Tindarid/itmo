package expression;

public abstract class Operation implements AnyExpression {
    protected AnyExpression firstOperand;
    protected AnyExpression secondOperand;

    public Operation(AnyExpression first, AnyExpression second) {
        firstOperand = first;
        secondOperand = second;
    }

    public int evaluate(int x) {
        return calc(firstOperand.evaluate(x), secondOperand.evaluate(x));
    }

    public double evaluate(double x) {
        return calc(firstOperand.evaluate(x), secondOperand.evaluate(x));
    }

    protected abstract double calc(double a, double b);
    protected abstract int calc(int a, int b);
}
