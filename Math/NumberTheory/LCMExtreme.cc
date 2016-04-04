/* Author: Ankit Sultana
 * Problem id: 1375
 * * * * * * * * * */
#include <stdio.h>
#include <cassert>
#define LL long long
#define MAXN 3000003

using namespace std;
unsigned LL phi[MAXN];

void precomp_phi() {
    phi[1] = 1;
    for(int i = 1; i < MAXN; i++){
        if(phi[i] == 0){
            for(int j = i*2; j < MAXN; j+=i){
                if(phi[j] == 0)	phi[j] = j;
                phi[j] = (phi[j]/i)*(i-1);
            }
        }
    }
    for(int i = 1; i < MAXN; i++) {
        if(phi[i] == 0) phi[i] = i-1;
    }
}

unsigned LL f[MAXN];
void precompute() {
    for(LL i = 1; i < MAXN; i++) {
        for(LL j = i; j < MAXN; j += i) {
            f[j] += phi[j/i] * (j/i);
        }
    }
    for(LL i = 1; i < MAXN; i++) {
        f[i]++;
    }
    for(int i = 0; i < MAXN; i++) {
        f[i] = i * (f[i]/2 - 1);
    }
    f[0] = 0;
    for(int i = 1; i < MAXN; i++) {
        f[i] = f[i-1] + f[i];
    }
}

int main() {
    precomp_phi();
    precompute();
    int t, n;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        printf("Case %d: %llu\n", tc, f[n]);
    }
    return 0;
}
