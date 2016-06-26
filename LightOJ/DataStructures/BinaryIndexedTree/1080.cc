/* Author: Ankit Sultana
 * Problem Name: Binary Simulation (1080)
 * * * * * * * * * * * * * * * */
#include <stdio.h>
#define MAXN 100001

int bitpool[10][MAXN];
int *bit = bitpool[0];
char input[MAXN];

int query(int x) {
    int res = 0;
    while(x) res += bit[x], x -= x & (-x);
    return res;
}
void update(int idx, int val) {
    while(idx < MAXN) bit[idx] += val, idx += idx & (-idx);
}

void invert(int i, int j) {
    update(i, 1);
    update(j+1, 1);
}
int get(int i) {
    return query(i);
}

int main() {
    int t, q, n, a, b;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        char opt;
        printf("Case %d:\n", tc);
        scanf("\n%s\n", input);
        scanf("%d\n", &q);
        while(q--) {
            scanf("%c", &opt);
            if(opt == 'I') {
                scanf("%d %d\n", &a, &b);
                invert(a, b);
            } else {
                scanf("%d\n", &a);
                if(get(a) % 2 == 1) {
                    printf("%d\n", 1 - int(input[a-1] - '0'));
                } else {
                    printf("%d\n", int(input[a-1]) - '0');
                }
            }
        }
        bit += MAXN;
    }
    return 0;
}
