using System;
using System.Collections.Generic;
using System.IO;
class Solution {
    static void Main(String[] args) {
        long expected = 200000;
        bool[] if_prime; if_prime = new bool[expected];
        for(int i = 0; i < expected; i++){
            if_prime[i] = true;
        }
        for(long i = 2; i < expected; i++){
            if(if_prime[i])
                for(long j = i*i; j < expected && j > 0; j+=i)
                    if_prime[j] = false;
        }
        int[] arr; arr = new int[expected];
        int size = 0;
        for(int i = 2;; i++){
            if(if_prime[i]){
                size+=1;
                arr[size] = i;
            }
            if(size >= 10000){
                break;
            }
        }
        int t, n;
        t = Convert.ToInt32(Console.ReadLine());
        for(int i = 0; i < t; i++){
            n = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine(arr[n]);
        }
    }
}
