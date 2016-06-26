/* Author: Ankit Sultana
 * Problem Name: Lucky Number (1097)
 * * * * * * * * * * */
#ifdef __APPLE__
    #include <iostream>
    using namespace std;
#endif
#include <stdio.h>
#define LIMIT 1429432
#define MAXN 100001
#define MID int mid = (l+r)>>1

int res[MAXN];
int tree[4*LIMIT];

void insert(int root, int l, int r, int x) {
    if(l == r) {
        tree[root] = 1;
        return ;
    }
    MID;
    if(x > mid) {
        insert(root*2+1, mid+1, r, x);
    } else {
        insert(root*2, l, mid, x);
    }
    tree[root] = tree[root*2] + tree[root*2+1];
}

void turnoff(int k, int root = 1, int l = 1, int r = LIMIT-1) {
    if(l == r) {
        tree[root] = 0;
        return ;
    }
    MID;
    if(k > mid) {
        turnoff(k, root*2+1, mid+1, r);
    } else {
        turnoff(k, root*2, l, mid);
    }
    tree[root] = tree[root*2] + tree[root*2+1];
}

int kth(int k, int root = 1, int l = 1, int r = LIMIT-1) {
    if(l == r) {
        return l;
    }
    MID;
    int res = -1;
    if(tree[root*2] < k) {
        k -= tree[root*2];
        res = kth(k, root*2+1, mid+1, r);
    } else {
        res = kth(k, root*2, l, mid);
    }
    return res;
}

int main() {
    for(int i = 1; i < LIMIT; i++) {
        insert(1, 1, LIMIT-1, i);
    }
    res[1] = 1;
    res[2] = 3;
    for(int k = 2; k < LIMIT; k += 2) {
        turnoff(k);
    }
    for(int i = 3; i < MAXN; i++) {
        int step = kth(i-1);
        for(int k = step; k <= tree[1]; k += step) {
            turnoff(kth(k));
            k--;
        }
        res[i] = kth(i);
    }
    int t;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        int x;
        scanf("%d", &x);
        printf("Case %d: %d\n", tc, res[x]);
    }
    return 0;
}
