package expression.type;

import expression.exceptions.OverflowException;

public class DoubleType extends AbstractType<Double> {
    public DoubleType parseImpl(String expr) {
        return new DoubleType(expr);
    }

    public DoubleType parseImpl(int a) {
        return new DoubleType(new Double(a));
    }

    public DoubleType(String expr) {
        value = new Double(expr);
    }

    public DoubleType(Double v) {
        value = v;
    }

    public Double addImpl(Double a) throws OverflowException {
        return value + a;
    }

    public Double subImpl(Double a) throws OverflowException {
        return value - a;
    }

    public Double divImpl(Double a) throws OverflowException {
        return value / a;
    }

    public Double mulImpl(Double a) throws OverflowException {
        return value * a;
    }

    public Double negImpl() throws OverflowException {
        return -value;
    }

    public Type<Double> valueOf(Double a) throws OverflowException {
        return new DoubleType(a);
    }
}
