package kz.nursan.rsa;

import java.math.BigInteger;
import java.util.Random;

public class Utils {
    private static BigInteger EXPONENT = BigInteger.valueOf(17);
    private static int BIT_LENGTH = 1024;

    public static Tuple genTuple() {
        try {
            BigInteger p = genPrime(), q = genPrime();
            BigInteger n = p.multiply(q);
            BigInteger phi = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
            BigInteger e = EXPONENT;
            BigInteger d = Utils.modInverse(e, phi);
            return new Tuple(e, d, n);
        } catch (ArithmeticException e) {
            return genTuple();
        }
    }

    public static byte[] transform(byte[] bytes, BigInteger n, BigInteger m) {
        BigInteger number = new BigInteger(bytes).add(m).mod(m);
        BigInteger transformed = pow(number, n, m);
        return transformed.toByteArray();
    }

    private static BigInteger genPrime() {
        return new BigInteger(BIT_LENGTH, 10000, new Random());
    }

    private static BigInteger pow(BigInteger a, BigInteger n, BigInteger mod) {
        return a.modPow(n, mod);
        // return a.modPow(n, mod);
    }

    private static BigInteger modInverse(BigInteger a, BigInteger m) throws ArithmeticException {
        GcdExt result = gcd(a, m);
        if (!result.gcd.equals(BigInteger.ONE)) {
            throw new ArithmeticException("P or Q was not prime");
        } else {
            return result.x.mod(m).add(m).mod(m);
        }
        // return a.modInverse(m);
    }

    private static class GcdExt {
        BigInteger gcd, x, y;

        public GcdExt(BigInteger gcd, BigInteger x, BigInteger y) {
            this.gcd = gcd;
            this.x = x;
            this.y = y;
        }
    }

    // a * x + b * y = gcd(a, b).
    // returns (gcd, x, y)
    private static GcdExt gcd(BigInteger a, BigInteger b) {
        if (a.equals(BigInteger.ZERO)) {
            return new GcdExt(b, BigInteger.ZERO, BigInteger.ONE);
        }
        GcdExt p = gcd(b.mod(a), a);
        return new GcdExt(p.gcd, p.y.subtract(b.divide(a).multiply(p.x)), p.x);
    }
}
