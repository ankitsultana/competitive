/* Author: Ankit Sultana
 * Problem Name: All Possible Increasing Subsequences (1085)
 * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <algorithm>
#define LL long long
#define mod 1000000007ll
#define MAXN 100001

using namespace std;
LL bitpool[10][MAXN];
LL arr[MAXN], cmp[MAXN];
LL *bit = bitpool[0];

void update(int x, LL val) {
    while(x < MAXN) {
        bit[x] += val;
        bit[x] %= mod;
        x += x & (-x);
    }
}
LL query(int x) {
    LL res = 0;
    while(x) {
        res += bit[x];
        res %= mod;
        x -= x & (-x);
    }
    return res;
}

int main() {
    int t;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        int n;
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%lld", &arr[i]);
            cmp[i] = arr[i];
        }
        cmp[0] = -2e10;
        sort(cmp, cmp + n + 1);
        int sz = 0;
        for(int i = 0; i <= n; i++)
            if(i == 0 || cmp[i] != cmp[i-1])
                cmp[sz++] = cmp[i];
        LL answer = 0;
        for(int i = 1; i <= n; i++) {
            LL temp = query(lower_bound(cmp, cmp + sz, arr[i]) - cmp - 1);
            answer += temp + 1;
            answer %= mod;
            update(lower_bound(cmp, cmp + sz, arr[i]) - cmp, temp + 1);
        }
        printf("%lld\n", answer);
        bit += MAXN;
    }
    return 0;
}
