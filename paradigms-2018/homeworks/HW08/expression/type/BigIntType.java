package expression.type;

import expression.exceptions.OverflowException;
import java.math.BigInteger;

public class BigIntType extends AbstractType<BigInteger> {
    public BigIntType parseImpl(String expr) {
        return new BigIntType(expr);
    }

    public BigIntType parseImpl(int a) {
        return new BigIntType(new BigInteger(Integer.toString(a)));
    }

    public BigIntType(String expr) {
        value = new BigInteger(expr);
    }

    public BigIntType(BigInteger v) {
        value = v;
    }

    public BigInteger addImpl(BigInteger a) throws OverflowException {
        return value.add(a);
    }

    public BigInteger subImpl(BigInteger a) throws OverflowException {
        return value.subtract(a);
    }

    public BigInteger divImpl(BigInteger a) throws OverflowException {
        if (a.compareTo(BigInteger.ZERO) == 0) {
            throw new OverflowException("Division by zero.");
        }
        return value.divide(a);
    }

    public BigInteger mulImpl(BigInteger a) throws OverflowException {
        return value.multiply(a);
    }

    public BigInteger negImpl() throws OverflowException {
        return value.negate();
    }

    public Type<BigInteger> valueOf(BigInteger a) throws OverflowException {
        return new BigIntType(a);
    }
}
