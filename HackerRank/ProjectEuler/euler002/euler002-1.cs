using System;
using System.Collections.Generic;
using System.IO;
class Solution {
    static void Main(String[] args) {
       long t, n;
       long[] fib;  fib = new long[100];
       fib[1] = 1; fib[2] = 2;
       for(int i = 3; i < 100; i++){
           fib[i] = fib[i-1]+fib[i-2];
           if(fib[i] > 40000000000000000){
               //Console.WriteLine("Hello");
               break;
           }
       }
       t = Convert.ToInt64(Console.ReadLine());
        for(long cnt = 0; cnt < t; cnt++){
            n = Convert.ToInt64(Console.ReadLine());
            long sum = 0;
            for(int i = 1; ; i++){
                if(fib[i] > n)
                    break;
                if(fib[i]%2 == 0){
                    sum += fib[i];
                }
            }    
            Console.WriteLine(sum);
        }
    }
}
