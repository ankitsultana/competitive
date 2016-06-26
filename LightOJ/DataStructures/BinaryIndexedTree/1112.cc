/* Author: Ankit Sultana
 * Problem Name: Curious Robin Hood (1112)
 * * * * * * * * * * * * * * * */
#include <stdio.h>
#define MAXN 100003
#define MAXT 5

int bitpool[MAXT][MAXN];
int *bit = bitpool[0];

void update(int x, int val) {
    while(x < MAXN) {
        bit[x] += val;
        x += x & (-x);
    }
}
int query(int x) {
    int res = 0;
    while(x) {
        res += bit[x];
        x -= x & (-x);
    }
    return res;
}

int main() {
    int t, opt, a, b, n, q;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:\n", tc);
        scanf("%d %d", &n, &q);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a);
            update(i, a);
        }
        while(q--) {
            scanf("%d", &opt);
            if(opt == 1) {
                scanf("%d", &a);
                a++;
                int val = query(a) - query(a-1);
                printf("%d\n", val);
                update(a, -val);
            } else if(opt == 2) {
                scanf("%d %d", &a, &b);
                a++;
                update(a, b);
            } else {
                scanf("%d %d", &a, &b);
                a++, b++;
                printf("%d\n", query(b) - query(a-1));
            }
        }
        bit += MAXN;
    }
    return 0;
}
