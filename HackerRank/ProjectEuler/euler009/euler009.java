import java.io.*;
import java.util.*;

public class euler009 {

	public static int isPerfectSquare(int x)
	{
		int temp = (int)(Math.sqrt(x) + 0.5);  
		return temp;
	}

	public static void main(String[] args)
	{
		final int MAXN = 3001;
		int[] is_poss = new int[MAXN];
		Arrays.fill(is_poss, -1);
		for(int i = 1; i < MAXN; i++){
			for(int j = 1; j < MAXN; j++){
				int temp = euler009.isPerfectSquare(i*i+j*j);
				if(temp*temp == i*i+j*j && temp+i+j < MAXN){
					is_poss[temp+i+j] = Math.max(temp*i*j, is_poss[temp+i+j]);
				}
			}
		}
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt(), n;
		while(t > 0){
			n = sc.nextInt();
			System.out.println(is_poss[n]);
			t--;
		}
	}
}
