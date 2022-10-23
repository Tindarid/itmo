import java.util.*;
import java.io.*;

public class Kenobi {
    static class Sword {
        public Sword next;
        public Sword prev;
        public int value;
        
        Sword(int s) {
            value = s;
            next = null;
            prev = null;
        }
    }
    public static void main(String [] argc) throws FileNotFoundException, IOException{
        Scanner in = new Scanner(new InputStreamReader(new FileInputStream("kenobi.in")));
        PrintWriter out = new PrintWriter(new File("kenobi.out")); 
        int n = in.nextInt();
        Sword head = new Sword(0);
        Sword middle = head;
        head.next = head;
        head.prev = head;
        int amount = 0;
        for (int i = 0; i < n; i++) {
            String s = in.next();
            if (s.equals("add")) {
                Sword temp = new Sword(in.nextInt());
                head.prev.next = temp;
                temp.next = head;
                temp.prev = head.prev;
                head.prev = temp;
                amount++;
                if (amount%2 == 1)
                    middle = middle.next;                                     
            } else if (s.equals("mum!") && amount > 1) {
                if (amount%2 == 0) middle = middle.next;
                Sword temp = head.prev;
                
                head.prev.next = head.next;
                head.next.prev = head.prev;
                middle.prev.next = head;
                
                
                head.prev = middle.prev;
                middle.prev = head;
                head.next = middle;
                
                middle = temp;
                    
            } else if (s.equals("take") && amount > 0) {
                if (amount%2 == 1)
                    middle = middle.prev;
                head.prev.prev.next = head;
                head.prev = head.prev.prev;
                amount--; 
                if (amount == 0) {
                    head.next = head;
                    head.prev = head;
                    middle = head;
                }
            }
        }
        out.print(amount + "\n");
        Sword temp = head.next;
        while (temp != head) {
            out.print(temp.value + " ");
            temp = temp.next;
        }
        out.print("\n");
        in.close();
        out.close();
    }
}