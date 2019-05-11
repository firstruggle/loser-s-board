/**
 *
 * @author alphawa
 */
import java.util.*;
import java.math.BigInteger;

public class Solution {
    
    public static class alpha {
        String name;
        BigInteger val;
    }
    
    public static class XYYcmp implements Comparator {
        public int compare(Object A, Object B) {
            alpha x = (alpha)A;
            alpha y = (alpha)B;
            return x.val.compareTo(y.val) < 0 ? 1 : -1;
        }
    }
    
    public static void main(String[] args) {
        Scanner read = new Scanner(System.in);
        int n = read.nextInt();
        BigInteger V = read.nextBigInteger();
        alpha[] a = new alpha[n];
        
        for (int i = 0; i < n; i++) {
            a[i] = new alpha();
            a[i].name = read.next();
            a[i].val = read.nextBigInteger();
        }
        Arrays.sort(a, new XYYcmp());//二维排序
        
        Vector<String> Ans = new Vector<String>();
        for (int i = 0; i < n; i++) {
            if (a[i].val.compareTo(V) <= 0) {//大整数的比较
                V = V.subtract(a[i].val);
                Ans.add(a[i].name);
            }
        }
        
        if (V.compareTo(BigInteger.valueOf(0)) != 0) {
            System.out.println(0);
        } else {
            System.out.println(Ans.size());
            for (int i = 0; i < Ans.size(); i++)
                System.out.println(Ans.elementAt(i));
        }
    }
    
}
