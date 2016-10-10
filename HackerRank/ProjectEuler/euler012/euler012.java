import java.io.*;
import java.util.*;

class Solution {
    public int count_divisors(long x) {
        int res = 1;
        long i = 2;
        while(i*i <= x) {
            int cnt = 0;
            while(x % i == 0) {
                x /= i;
                cnt += 1;
            }
            res *= (cnt + 1);
            i += 1;
        }
        if(x != 1) res *= 2;
        return res;
    }
    public long tri(long x) {
        return x * (x + 1) / 2;
    }
    public static void main(String[] args) {
        Solution A = new Solution();
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while(t > 0) {
            int n = sc.nextInt(), i = 1;
            while(A.count_divisors(A.tri(i)) <= n) {
                i++;
            }
            System.out.println(A.tri(i));
            t--;
        }
    }
}
