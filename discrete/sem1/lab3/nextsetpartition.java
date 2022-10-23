import java.io.*;
import java.util.*;

public class nextsetpartition {
    public static void main(String [] argc) throws IOException, FileNotFoundException {
        BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("nextsetpartition.in"), "utf-8"));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(new FileOutputStream("nextsetpartition.out"), "utf-8"));
        while (in.ready()) {
            List<List<Integer>> numbers = new ArrayList<List<Integer>>();
            Scanner scan = new Scanner(in.readLine());
            int n = scan.nextInt();
            int k = scan.nextInt();
            if (n == 0 && k == 0) {
                break;
            }
            for (int i = 0; i < k; i++) {
                scan = new Scanner(in.readLine());
                numbers.add(new ArrayList<Integer>());
                while (scan.hasNextInt()) {
                    numbers.get(i).add(scan.nextInt());
                }
            }
            in.readLine();
            TreeSet<Integer> deleted = new TreeSet<Integer>();
            boolean flag = true;
            for (int i = numbers.size() - 1; i >= 0 && flag; i--) {
                if (!deleted.isEmpty()) {
                    if(deleted.higher(numbers.get(i).get(numbers.get(i).size() - 1)) != null) {
                        int temp = deleted.higher(numbers.get(i).get(numbers.get(i).size() - 1));
                        numbers.get(i).add(temp);
                        deleted.remove(temp);
                        break;
                    }
                }
                for (int j = numbers.get(i).size() - 1; j >= 1; j--) {
                    if (!deleted.isEmpty() && deleted.higher(numbers.get(i).get(j)) != null) {
                        int temp = deleted.higher(numbers.get(i).get(j));
                        deleted.remove(temp);
                        deleted.add(numbers.get(i).get(j));
                        numbers.get(i).set(j, temp);
                        flag = false;
                        break;
                    } else {
                        deleted.add(numbers.get(i).get(j));
                        numbers.get(i).remove(j);
                    }
                }
                if (flag) {
                    deleted.add(numbers.get(i).get(0));
                    numbers.get(i).remove(0);
                    k--;
                }
            }
            while (!deleted.isEmpty()) {
                numbers.add(Collections.singletonList(deleted.first()));
                deleted.remove(deleted.first());
                k++;
            }

            out.write(n + " " + k + "\n");
            for (int i = 0; i < numbers.size(); i++) {
                if (!numbers.get(i).isEmpty()) {
                    for (int j = 0; j < numbers.get(i).size(); j++) {
                        out.write(numbers.get(i).get(j) + " ");
                    }
                    out.write("\n");
                }
            }
            out.write("\n");
        }
        in.close();
        out.close();
    }
}
