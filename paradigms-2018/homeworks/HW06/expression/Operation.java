package expression;

public abstract class Operation implements CommonExpression {
    protected CommonExpression firstOperand;
    protected CommonExpression secondOperand;
    protected CommonExpression thirdOperand;

    public Operation(CommonExpression first, CommonExpression second) {
        firstOperand = first;
        secondOperand = second;
    }

    public Operation(CommonExpression first, CommonExpression second, CommonExpression third) {
        firstOperand = first;
        secondOperand = second;
        thirdOperand = third;
    }

    public int evaluate(int x, int y, int z) {
        return calc(firstOperand.evaluate(x, y, z), secondOperand.evaluate(x, y, z));
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
