/* Author: Ankit Sultana
 * Problem id: 1024
 * * * * * * * * * */
import java.math.BigInteger;
import java.util.*;

class Main {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		final int MAXN = 1003;
		int t = sc.nextInt();
		for(int tc = 1; tc <= t; tc++) {
			int n = sc.nextInt(), inp;
			BigInteger res, temp;
			res = new BigInteger("-1");
			for(int i = 1; i <= n; i++) {
				inp = sc.nextInt();
				temp = new BigInteger(Integer.toString(inp));
				if(i == 1) {
					res = temp;
				} else {
					res = res.multiply(temp).divide(res.gcd(temp));
				}
			}
			System.out.println("Case " + tc + ": " + res);
			System.gc();
		}
	}
}
