import java.util.*;
import java.io.*;

public class Formation {
    static class Soldier {
        public Soldier next;
        public Soldier prev;
        public int value;
        
        Soldier(int s) {
            value = s;
            next = null;
            prev = null;
        }
    }
    public static void main(String [] argc) throws FileNotFoundException, IOException{
        Scanner in = new Scanner(new InputStreamReader(new FileInputStream
            ("formation.in")));
        PrintWriter out = new PrintWriter(new File("formation.out")); 

        int n = in.nextInt(), m = in.nextInt();
        List<Soldier> mas = new ArrayList<Soldier>();
        for (int i = 0; i <= n; i++)
            mas.add(new Soldier(i));
        
        Soldier head = mas.get(0);
        Soldier first = mas.get(1);
        head.next = first; first.next = head;
        head.prev = first; first.prev = head;
        
        for (int i = 0; i < m; i++) {
            String s = in.next();
            if (s.equals("left")) {
                Soldier temp1 = mas.get(in.nextInt());
                Soldier temp2 = mas.get(in.nextInt());
                temp1.next = temp2;
                temp1.prev = temp2.prev;
                temp2.prev.next = temp1;
                temp2.prev = temp1;                
            } else if (s.equals("right")) {
                Soldier temp1 = mas.get(in.nextInt());
                Soldier temp2 = mas.get(in.nextInt());
                temp1.prev = temp2;
                temp1.next = temp2.next;
                temp2.next.prev = temp1;
                temp2.next = temp1;
            } else if (s.equals("leave")) {
                Soldier temp1 = mas.get(in.nextInt());
                (temp1.prev).next = temp1.next;
                (temp1.next).prev = temp1.prev;
                temp1.next = null;
                temp1.prev = null;
            } else if (s.equals("name")) {
                Soldier temp1 = mas.get(in.nextInt());
                out.print((temp1.prev).value + " " + (temp1.next).value + "\n");              
            }
        }
        in.close();
        out.close();
    }
}