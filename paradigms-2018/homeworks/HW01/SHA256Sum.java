import java.util.*;
import java.io.*;
import java.security.*;
import java.nio.file.*;
import java.nio.*;
import javax.xml.bind.DatatypeConverter;

public class SHA256Sum {
    private static void getHash(InputStream in, String name) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] buffer = new byte[1 << 16];
            int r;
            while ((r = in.read(buffer)) != -1) {
                md.update(buffer, 0, r);
            }
            System.out.println(DatatypeConverter.printHexBinary(md.digest()).toUpperCase() + " *" + name);
        } catch (IOException e) {
            System.out.println("IOException: " + e.getMessage());
        } catch (NoSuchAlgorithmException e) {
            System.out.println("SHA-256 is not supported");
        }
    }

    public static void main(String[] args) {
        if (args.length == 0) {
            getHash(System.in, "-");
            return;
        }
        for (String filename : args) {
            try {
                getHash(Files.newInputStream(Paths.get(filename)), filename);
            } catch (InvalidPathException e) {
                System.out.println("Name of file \"" + filename + "\" is invalid");
            } catch (SecurityException e) {
                System.out.println("Cannot access file: " + filename);
            } catch (IOException e) {
                System.out.println("IOException: " + e.getMessage());
            }
        }
    }
}
