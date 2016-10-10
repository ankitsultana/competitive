#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int t, k, n, i;
    scanf("%d", &t);
    char s[2000];
    while(t--){
        scanf("%d %d", &n, &k);
        scanf("%s", s);
        int maxim = 1, res;
        for(i = 0; i < k; i++){
            maxim = maxim*(s[i]-48);
        }
        res = maxim;
        for(i = k; i < n; i++){
            maxim = maxim*(s[i]-48);
            if(s[i-k] == 48){
                maxim = 1;
                int j;
                for(j = i-k+1; j <= i; j++){
                    maxim = maxim*(s[j]-48);
                }
            }
            else
                maxim /= s[i-k]-48;
            res = maxim>res?maxim: res;
        }
        printf("%d\n", res);
    }
    return 0;
}
