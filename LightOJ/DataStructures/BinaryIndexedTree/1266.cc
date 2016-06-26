/* Author: Ankit Sultana
 * Problem Name: Points in Rectangle (1266)
 * * * * * * * * * * * * * * * * */
#ifdef __APPLE__
    #include <iostream>
#endif
#include <stdio.h>
#include <algorithm>
#define MAXN 1010
#define OFFSET 1

using namespace std;
int bit[MAXN][MAXN];
bool vis[MAXN][MAXN];

int query_y(int x, int q) {
    int res = 0;
    while(q > 0) {
        res += bit[x][q], q -= q & (-q);
    }
    return res;
}
void update_y(int x, int idx, int val) {
    while(idx < MAXN) {
        bit[x][idx] += val;
        idx += idx & (-idx);
    }
}
void update(int x, int y, int val) {
    while(x < MAXN) {
        update_y(x, y, val);
        x += x & (-x);
    }
}
int query(int x, int y1, int y2) {
    int res = 0;
    while(x > 0) {
        res += query_y(x, y2) - query_y(x, y1 - 1);
        x -= x & (-x);
    }
    return res;
}

int main() {
    int x, y, x1, y1, y2, x2, opt, q, t;
#ifdef __APPLE__
    freopen("input.in", "rb", stdin);
#endif
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:\n", tc);
        scanf("%d", &q);
        while(q--) {
            scanf("%d", &opt);
            if(opt == 1) {
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                x1 += OFFSET, y1 += OFFSET, x2 += OFFSET, y2 += OFFSET;
                // printf("%d %d\n", query(x2, y1, y2), query(x1-1, y1, y2));
                printf("%d\n", query(x2, y1, y2) - query(x1-1, y1, y2));
            } else {
                scanf("%d %d", &x, &y);
                x += OFFSET, y += OFFSET;
                if(!vis[x][y]) {
                    vis[x][y] = true;
                    update(x, y, 1);
                }
            }
        }
        // reset
        for(int i = 0; i < MAXN; i++) for(int j = 0; j < MAXN; j++) bit[i][j] = 0, vis[i][j] = false;
    }
    return 0;
}
