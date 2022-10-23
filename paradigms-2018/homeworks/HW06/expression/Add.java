package expression;

public class Add extends Operation {
    public Add(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    public double calc(double a, double b) {
        return a + b;
    }

    public int calc(int a, int b) {
        return a + b;
    }
}
