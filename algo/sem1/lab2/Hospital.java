import java.util.*;
import java.io.*;

public class Hospital {
    static class Patient {
        public Patient next;
        public Patient prev;
        public int value;
        
        Patient(int s) {
            value = s;
            next = null;
            prev = null;
        }
    }
    public static void main(String [] argc) throws FileNotFoundException, IOException{
        Scanner in = new Scanner(new InputStreamReader(new FileInputStream("hospital.in")));
        PrintWriter out = new PrintWriter(new File("hospital.out")); 
        Patient head = new Patient(0);
        Patient middle = head;
        head.next = head;
        head.prev = head;
        int n = in.nextInt();
        int amount = 0;
        for (int i = 0; i < n; i++) {
            String s = in.next();
            if (s.equals("+")) {
                Patient temp = new Patient(in.nextInt());
                head.prev.next = temp;
                temp.next = head;
                temp.prev = head.prev;
                head.prev = temp;
                if (amount%2 == 0)
                    middle = middle.next;
                amount++;               
            } else if (s.equals("*")) {
                Patient temp = new Patient(in.nextInt());              
                temp.prev = middle;
                temp.next = middle.next;
                middle.next.prev = temp;
                middle.next = temp;
                if (amount%2 == 0)
                    middle = middle.next;
                amount++;
            } else if (s.equals("-")) {
                out.write(head.next.value + "\n");
                if (amount%2 == 0)
                    middle = middle.next;
                head.next.next.prev = head;
                head.next = head.next.next;
                amount--; 
                if (amount == 0) {
                    head.next = head;
                    head.prev = head;
                    middle = head;
                }
            }
        }
        in.close();
        out.close();
    }
}