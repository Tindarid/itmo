package search;

public class BinarySearchMissing {
    //Pre: arr != null && (forall i = 0...arr.length - 2 : a[i] >= a[i + 1]) && 0 <= r && r < arr.length && l >= 0 && l < arr.length && l <= r
    //Post: (((i = min(l..r - 1) && arr[i] <= x && R = i) 
    //      || (l <= R <= r && a[R] < x && a[R + 1] > x) || (R = arr.length && forall i = 0...arr.length - 1 : arr[i] > x)) 
    //      && forall i = 0...arr.length - 1 : arr'[i] = arr[i] 
    private static int recBin(int arr[], int l, int r, int x) {
        if (l < r) {
            //r >= 0 && r < arr.length && l >= 0 && l < arr.length
            int m = l + (r - l) / 2;
            //m' == (r + l) / 2 && r == r' && l == l'

            //arr[m] <= x && 
            //m >= 0 && m < arr.length && m == (r + l) / 2 && r >= 0 && r < arr.length && l >= 0 && l < arr.length
            if (arr[m] <= x) {
                //i >= 2 && forall i = 0...arr.length - 2 && a[i] >= a[i + 1] || arr.length == 1 && 
                //i = min(0..arr.length - 1) && a[i] <= x && R == a[i] 
                return recBin(arr, l, m, x);
            } else {
                //i >= 2 && forall i = 0...arr.length - 2 && a[i] >= a[i + 1] || arr.length == 1 && 
                //i = min(0..arr.length - 1) && a[i] <= x && R == a[i] 
                return recBin(arr, m + 1, r, x);
            }
        }
        //l' >= r'
        // ->
        //Post
        return r;
    }

    //Pre: arr != null && (forall i = 0...arr.length - 2 : a[i] >= a[i + 1]) && 0 <= r && r < arr.length && l >= 0 && l < arr.length && l <= r
    //Post: (((i = min(l..r - 1) && arr[i] <= x && R = i) 
    //      || (l <= R <= r && a[R] < x && a[R + 1] > x) || (R = arr.length && forall i = 0...arr.length - 1 : arr[i] > x)) 
    //      && forall i = 0...arr.length - 1 : arr'[i] = arr[i] 
    private static int iterBin(int arr[], int l, int r, int x) {
        //inv:
        //r' <= i && l' < i && 
        //r >= 0 && r < arr.length && l >= 0 && l < arr.length
        while (l < r) {
            //r >= 0 && r < arr.length && l >= 0 && l < arr.length
            int m = l + (r - l) / 2;
            //m' == (r + l) / 2

            //arr[m] <= x && 
            //m >= 0 && m < arr.length && m == (r + l) / 2 && r >= 0 && r < arr.length && l >= 0 && l < arr.length
            if (arr[m] <= x) {
                //m >= 0 && m < arr.length && m == (r + l) / 2 && r >= 0 && r < arr.length && l >= 0 && l < arr.length
                r = m;
                //r' == m
            } else {
                //m >= 0 && m < arr.length && m == (r + l) / 2 && r >= 0 && r < arr.length && l >= 0 && l < arr.length
                l = m + 1;
                //l' == m && l' < arr.length
            }
        }
        //l' >= r'
        // ->
        //Post
        return r;
    }

    //Pre: args.lengh > 0
    public static void main(String[] args) {
        if (args.length <= 1) {
            System.out.println("-1");
            return;
        }
        try {
            int x = Integer.parseInt(args[0]);
            int[] a = new int[args.length - 1];
            for (int i = 1; i < args.length; i++) {
                a[i - 1] = Integer.parseInt(args[i]);
            }
            int temp = iterBin(a, 0, a.length, x);
            if (temp == recBin(a, 0, a.length, x)) {
                if (temp != a.length && a[temp] == x) {
                    System.out.println(temp);
                } else {
                    System.out.println(-temp - 1);
                }
            }
        } catch (NumberFormatException e) {
            System.out.println("Incorrect input, use digits");
        }
    }
}
