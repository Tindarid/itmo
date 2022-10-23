package expression;

public class Negate implements CommonExpression {
    CommonExpression expr;

    public Negate(CommonExpression temp) {
        expr = temp;
    }

    public int evaluate(int x, int y, int z) {
        return -expr.evaluate(x, y, z);
    }

    public int evaluate(int x) {
        return -expr.evaluate(x);
    }

    public double evaluate(double x) {
        return -expr.evaluate(x);
    }
}
