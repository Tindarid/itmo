import java.util.*;
import java.io.*;

public class Lzw {
    public static void main(String [] argc) throws FileNotFoundException, IOException {
        String s;
        Map<String, Integer> letters = new TreeMap<String, Integer>();
        Scanner in = new Scanner(new BufferedReader(
            new InputStreamReader(new FileInputStream("lzw.in"))));
        PrintWriter out = new PrintWriter(new File("lzw.out")); 
        s = in.next();
        
        for (char i = 'a'; i <= 'z'; i++) {
            letters.put(i + "", i - 'a');
        }
        letters.put("", -1);
        char c; String temp = "" + s.charAt(0); int i = 0, glc = 26;
        while (true) {
            i++;
            if (i == s.length()) {
                out.print(letters.get(temp) + "\n");
                break;
            }
            c = s.charAt(i);
            
            if (letters.containsKey(temp + c)) {
                temp += c;
                continue;
            }
            
            out.print(letters.get(temp) + " ");
            letters.put(temp + c, glc++);
            temp = c + "";            
        }
        
        in.close();
        out.close();
    }
}