//C++也可以写
import java.util.Scanner;
 
public class Main {
	public static int gcd(int a, int b) {//求两个数的最大公约数
		if (b > 0) return gcd(b, a % b);
        return a;
	}
 
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		String xiaoshu = in.next();
 
		String[] array = new String[2];
		array = xiaoshu.split("\\.");
		int a = Integer.parseInt(array[0]);//获取整数部分
		int b = Integer.parseInt(array[1]);//获取小数部分
		int length = array[1].length();
		int FenZi = (int) (a * Math.pow(10, length) + b);
		int FenMu = (int) Math.pow(10, length);
		int MaxYueShu = gcd(FenZi, FenMu);
		System.out.println(FenZi / MaxYueShu + "/" + FenMu / MaxYueShu);
	}
 
}


