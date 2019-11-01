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
        int n = read.nextInt();//读int
        BigInteger V = read.nextBigInteger();//读bigint
        alpha[] a = new alpha[n];//开数组
        
        for (int i = 0; i < n; i++) {
            a[i] = new alpha();
            a[i].name = read.next();//读字符串，空格分割
            a[i].val = read.nextBigInteger();
        }
        Arrays.sort(a, new XYYcmp());//二维排序
        
        Vector<String> Ans = new Vector<String>();//开vector
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

/*java读EOF：while (read.hasNext()) {}
 *java开数组：static int a[] = new int[maxn];
 *java随机数：import java.util.Random
            Random ra = new Random();
            int x = ra.nextInt(100);//[0,100)
            double y = ra.nextDouble();//[0.0,1.0)
 *BigInteger：a.compareTo(b) < 0;//大整数a与b的比较: a < b
             BigInteger.valueOf(int);//int类型化为大整数
             a.add\subtract\multiply\divide\mod(b);//大整数a加减乘除模b
 *关于传引用必须用class
    public class Main {
	static class myobj {
		int b;
		myobj(int x) { 
			b = x;
		}
	}
	
	static public void test(int a) {
		a = a + 1;
		System.out.println(a);
	}
	
	static public void test2(myobj c) {
		c.b++;
		System.out.println(c.b);
	}
	
	public static void main(String[] args) {
		int x = 10;
		test(x);
		System.out.println(x);
		myobj c = new myobj(x);
		test2(c);
		System.out.println(c.b);
	}
}
**/

    
