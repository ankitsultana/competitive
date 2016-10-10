#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    long long t, n, res, i;
    scanf("%lld", &t);
    while(t--){
        scanf("%lld", &n);
        res = -1;
        for(i = 2; i*i <= n; i++){
            while(n%i == 0){
                n /= i;
            }
            if(n == 1){
                res = i;
            }
        }
        if(res == -1)
            res = n;
        printf("%lld\n", res);
    }
    return 0;
}

