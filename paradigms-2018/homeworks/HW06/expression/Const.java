package expression;

public class Const implements CommonExpression {
    Number value;

    public Const(Number v) {
        value = v;
    }

    public int evaluate(int x, int y, int z) {
        return value.intValue();
    }

    public int evaluate(int x) {
        return value.intValue();
    }

    public double evaluate(double x) {
        return value.doubleValue();
    }
}
