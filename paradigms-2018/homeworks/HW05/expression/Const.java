package expression;

public class Const implements AnyExpression {
    Number value;

    public Const(Number v) {
        value = v;
    }

    public int evaluate(int x) {
        return value.intValue();
    }

    public double evaluate(double x) {
        return value.doubleValue();
    }
}
