package expression.type;

import expression.exceptions.OverflowException;

public class UnsafeLongType extends AbstractType<Long> {
    public UnsafeLongType parseImpl(String expr) {
        return new UnsafeLongType(expr);
    }

    public UnsafeLongType parseImpl(int a) {
        return new UnsafeLongType(new Long(a));
    }

    public UnsafeLongType(String expr) {
        value = new Long(expr);
    }

    public UnsafeLongType(Long v) {
        value = v;
    }

    public Long addImpl(Long a) throws OverflowException {
        return value + a;
    }

    public Long subImpl(Long a) throws OverflowException {
        return value - a;
    }

    public Long divImpl(Long a) throws OverflowException {
        return value / a;
    }

    public Long mulImpl(Long a) throws OverflowException {
        return value * a;
    }

    public Long negImpl() throws OverflowException {
        return -value;
    }

    public Type<Long> valueOf(Long a) throws OverflowException {
        return new UnsafeLongType(a);
    }
}
