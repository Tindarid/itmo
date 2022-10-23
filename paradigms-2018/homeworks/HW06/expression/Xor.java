package expression;

public class Xor extends Operation {
    public Xor(CommonExpression first, CommonExpression second) {
        super(first, second);
    }

    public double calc(double a, double b) {
        return 0;
    }

    public int calc(int a, int b) {
        return a ^ b;
    }
}
