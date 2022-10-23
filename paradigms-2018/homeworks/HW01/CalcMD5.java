import java.util.*;
import java.io.*;
import java.security.*;
import java.nio.file.*;
import java.nio.*;
import javax.xml.bind.DatatypeConverter;

public class CalcMD5 {
    public static void main(String[] argc) {
        if (argc.length != 1) {
            System.out.println("Use java CalcMD5 *filename*");
            return;
        }
        MessageDigest md;
        try {
            md = MessageDigest.getInstance("MD5");
        } catch (NoSuchAlgorithmException e) {
            System.out.println("MD5 is not supported");
            return;
        }
        List<String> files;
        try {
            files = Files.readAllLines(Paths.get(argc[0])); 
        } catch (IOException e) {
            System.out.println("IOException: " + e.getMessage());
            return;
        } catch (InvalidPathException e) {
            System.out.println("Filename is invalid");
            return;
        } catch (SecurityException e) {
            System.out.println("Cannot access file");
            return;
        } 
        for (String filename : files) {
            try {
                InputStream in = Files.newInputStream(Paths.get(filename));
                byte[] buffer = new byte[1 << 16];
                int r;
                while ((r = in.read(buffer)) != -1) {
                    md.update(buffer, 0, r);
                }
                System.out.println(DatatypeConverter.printHexBinary(md.digest()).toUpperCase());
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
