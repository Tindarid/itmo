package expression.test;

import expression.*;
import expression.type.*;
import expression.generic.*;

public class Main {
    public static void main(String[] args) throws Exception {
        if (args.length == 0) {
            return;
        }
        int x1 = 1;
        int x2 = 10;
        int y1 = 1;
        int y2 = 10;
        int z1 = 1;
        int z2 = 10;
        String expr = "1 + 2 + 3 + 4 + x";
        GenericTabulator tabulator = new GenericTabulator();
        Object[][][] arr = tabulator.tabulate(args[0].substring(1), expr, x1, x2, y1, y2, z1, z2);
        for (Object i[][] : arr) {
            System.out.println();
            for (Object j[] : i) {
                System.out.println();
                for (Object k : j) {
                    System.out.print(k + " ");
                }
            }
        }
    }
}
