using System;
using System.Collections.Generic;
using System.IO;
class Solution {
    static int max(int a, int b)
    {
        if(a > b)   return a;
        return b;
    }
    
    static void Main(String[] args) {
        int t = Convert.ToInt32(Console.ReadLine());
        int[] if_prime;    if_prime = new int[50];
        for(int i = 0; i < 50; i++)
            if_prime[i] = 1;
        if_prime[0] = (if_prime[1] = 0);
        for(int i = 2; i < 50; i++)
            if(if_prime[i] == 1)
                for(int j = i*i; j < 50; j+=i)
                    if_prime[j] = 0;
        while(t != 0){
            t--;
            int[] MaxPower;
            MaxPower = new int[50];
            for(int i = 0; i < 50; i++) MaxPower[i] = 0;
            int n = Convert.ToInt32(Console.ReadLine());
            long res = 1;
            for(int i = 1; i <= n; i++){
                for(int j = 2; j <= i; j++){
                    int temp = i, power = 0;
                    while(if_prime[j] == 1 && temp % j == 0){
                        MaxPower[j] = max(MaxPower[j], ++power);
                        temp /= j;
                    }
                }
            }
            for(int j = 2; j <= n; j++){
                while(MaxPower[j] != 0){
                    res = res*j;
                    MaxPower[j]--;
                }
            }
            Console.WriteLine(res);
        }
    }
}
