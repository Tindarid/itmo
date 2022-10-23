package kz.nursan;

import kz.nursan.rsa.Tuple;
import kz.nursan.rsa.Utils;

import java.util.Arrays;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        test();
    }

    public static void test() {
        Random r = new Random();
        for (int i = 0; i < 100; ++i) {
            byte[] bytes = new byte[250]; // lets encode 250 bytes (< 2048 bit)
            r.nextBytes(bytes);
            for (int j = 0; j < 250; ++j) {
                if (bytes[j] < 0) {
                    bytes[j] = (byte)-bytes[j];
                }
                if (bytes[j] <= 0) {
                    bytes[j] = 1;
                }
            }
            String message = new String(bytes);
            Tuple t = Utils.genTuple();

            byte[] coded = Utils.transform(message.getBytes(), t.openExp, t.mod);
            byte[] decoded = Utils.transform(coded, t.secretExp, t.mod);

            String decodedString = new String(decoded);
            if (!message.equals(decodedString)) {
                System.out.println("On iteration " + i);
                System.out.println("Message: " + message);
                System.out.println("Decoded: " + decodedString);
                System.out.println(Arrays.toString(bytes));
                System.out.println(Arrays.toString(coded));
                System.out.println(Arrays.toString(decoded));
                throw new RuntimeException();
            } else {
                System.out.println("Test " + (i + 1) + ": OK");

            }
        }
    }
}
