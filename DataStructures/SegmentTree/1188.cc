/* Author: Ankit Sultana
 * Problem Name: Fast Queries (1188)
 * * * * * * * * * * */
#ifdef __APPLE__
    #include <iostream>
#endif
#include <cstdio>
#include <algorithm>
#include <functional>
#define F first
#define S second
#define MAXN 100003

using namespace std;
typedef pair<pair<int, int>, int> pt;

int tree[4*MAXN], n, arr[MAXN], last_seen[MAXN], nxt[MAXN];

void reset(int root = 1, int l = 1, int r = n) {
    tree[root] = 0;
    if(l == r)  return ;
    int mid = (l + r) >> 1;
    reset(root*2, l, mid);
    reset(root*2+1, mid+1, r);
}
void update(int idx, int val, int root = 1, int l = 1, int r = n) {
    if(l == r) {
        tree[root] += val;
        return ;
    }
    int mid = (l + r) >> 1;
    if(idx <= mid)  update(idx, val, root*2, l, mid);
    else update(idx, val, root*2+1, mid+1, r);
    tree[root] = tree[root*2] + tree[root*2+1];
}
int query(int qr, int root = 1, int l = 1, int r = n) {
    if(r <= qr) return tree[root];
    else if(l > qr) return 0;
    int mid = (l + r) >> 1, res;
    res = query(qr, root*2, l, mid);
    if(mid < qr)
        res += query(qr, root*2+1, mid+1, r);
    return res;
}

pt qs[5*MAXN];
int res[5*MAXN];

int main() {
    int t, l, r, q;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:\n", tc);
        scanf("%d %d", &n, &q);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
        }
        for(int i = n; i > 0; i--) {
            nxt[i] = last_seen[arr[i]];
            last_seen[arr[i]] = i;
        }
        for(int i = 0; i < q; i++) {
            scanf("%d %d", &l, &r);
            qs[i].F.F = l, qs[i].F.S = r, qs[i].S = i;
        }
        sort(qs, qs + q, greater<pt>());
        int iter = n;
        for(int i = 0; i < q; i++) {
            while(iter > 0 && iter >= qs[i].F.F) {
                update(iter, 1);
                if(nxt[iter])   update(nxt[iter], -1);
                iter--;
            }
            res[qs[i].S] = query(qs[i].F.S);
        }
        for(int i = 0; i < q; i++) {
            printf("%d\n", res[i]);
        }
        reset();
        for(int i = 1; i <= n; i++)
            last_seen[arr[i]] = 0;
    }
    return 0;
}
