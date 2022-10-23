package kz.nursan.rsa;

import java.math.BigInteger;

public class Tuple {
    public BigInteger openExp;
    public BigInteger secretExp;
    public BigInteger mod;

    public Tuple(BigInteger openExp, BigInteger secretExp, BigInteger mod) {
        this.openExp = openExp;
        this.secretExp = secretExp;
        this.mod = mod;
    }
}
