package expression.type;

import expression.exceptions.OverflowException;

public class UnsafeShortType extends AbstractType<Short> {
    public UnsafeShortType parseImpl(String expr) {
        return new UnsafeShortType(expr);
    }

    public UnsafeShortType parseImpl(int a) {
        return new UnsafeShortType(new Short((short)a));
    }

    public UnsafeShortType(String expr) {
        value = new Short(expr);
    }

    public UnsafeShortType(Short v) {
        value = v;
    }

    public Short addImpl(Short a) throws OverflowException {
        return (short)(value + a);
    }

    public Short subImpl(Short a) throws OverflowException {
        return (short)(value - a);
    }

    public Short divImpl(Short a) throws OverflowException {
        return (short)(value / a);
    }

    public Short mulImpl(Short a) throws OverflowException {
        return (short)(value * a);
    }

    public Short negImpl() throws OverflowException {
        return (short)(-value);
    }

    public Type<Short> valueOf(Short a) throws OverflowException {
        return new UnsafeShortType(a);
    }
}
