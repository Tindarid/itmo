package expression;

public class Variable implements CommonExpression {
    String var;

    public Variable(String v) {
        var = v;
    }

    public int evaluate(int x, int y, int z) {
        if (var.equals("x")) {
            return x;
        } else if (var.equals("y")) {
            return y;
        } else if (var.equals("z")) {
            return z;
        } else {
            return 0;
        }
    }

    public int evaluate(int x) {
        return x;
    }

    public double evaluate(double x) {
        return x;
    }
}
