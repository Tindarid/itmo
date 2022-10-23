package expression.type;

import expression.exceptions.OverflowException;

public class UnsafeIntType extends AbstractType<Integer> {
    public UnsafeIntType parseImpl(String expr) {
        return new UnsafeIntType(expr);
    }

    public UnsafeIntType parseImpl(int a) {
        return new UnsafeIntType(new Integer(a));
    }

    public UnsafeIntType(String expr) {
        value = new Integer(expr);
    }

    public UnsafeIntType(Integer v) {
        value = v;
    }

    public Integer addImpl(Integer a) throws OverflowException {
        return value + a;
    }

    public Integer subImpl(Integer a) throws OverflowException {
        return value - a;
    }

    public Integer divImpl(Integer a) throws OverflowException {
        return value / a;
    }

    public Integer mulImpl(Integer a) throws OverflowException {
        return value * a;
    }

    public Integer negImpl() throws OverflowException {
        return -value;
    }

    public Type<Integer> valueOf(Integer a) throws OverflowException {
        return new UnsafeIntType(a);
    }
}
