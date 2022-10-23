package expression.type;

import expression.exceptions.OverflowException;

public class SafeIntType extends AbstractType<Integer> {
    public SafeIntType parseImpl(String expr) {
        return new SafeIntType(expr);
    }

    public SafeIntType parseImpl(int a) {
        return new SafeIntType(new Integer(a));
    }

    public SafeIntType(String expr) {
        value = new Integer(expr);
    }

    public SafeIntType(Integer v) {
        value = v;
    }

    public Integer addImpl(Integer a) throws OverflowException {
        if ((Integer.MAX_VALUE - value < a && value > 0) || (Integer.MIN_VALUE - value > a && value < 0)) {
            throw new OverflowException("Overflow.");
        } 
        return value + a;
    }

    public Integer subImpl(Integer a) throws OverflowException {
        if ((Integer.MAX_VALUE + a < value && a < 0) || (Integer.MIN_VALUE + a > value && a > 0)) {
            throw new OverflowException("Overflow.");
        } 
        return value - a;
    }

    public Integer divImpl(Integer a) throws OverflowException {
        if (a == 0) {
            throw new OverflowException("Division by zero.");
        }
        if (value == Integer.MIN_VALUE && a == -1) {
            throw new OverflowException("Overflow.");
        }
        return value / a;
    }

    public Integer mulImpl(Integer a) throws OverflowException {
        if (value > 0 && a > 0 && Integer.MAX_VALUE / value < a) {
            throw new OverflowException("Overflow.");
        }
        if (value > 0 && a < 0 && Integer.MIN_VALUE / value > a) {
            throw new OverflowException("Overflow.");
        }
        if (value < 0 && a > 0 && Integer.MIN_VALUE / a > value) {
            throw new OverflowException("Overflow.");
        }
        if (value < 0 && a < 0 && Integer.MAX_VALUE / value > a) {
            throw new OverflowException("Overflow.");
        }
        return value * a;
    }

    public Integer negImpl() throws OverflowException {
        if (value == Integer.MIN_VALUE) {
            throw new OverflowException("Overflow.");
        }
        return -value;
    }

    public Type<Integer> valueOf(Integer a) throws OverflowException {
        return new SafeIntType(a);
    }
}
