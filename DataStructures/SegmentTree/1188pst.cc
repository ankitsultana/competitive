/* Author: Ankit Sultana
 * Problem Name: Fast Queries (1188)
 * * * * * * * * * * */
#ifdef __APPLE__
    #include <iostream>
#endif
#include <cstdio>
#define MAXN 100003

using namespace std;

struct node {
    int val;
    node *l, *r;
    node() {
        this->val = 0;
        l = r = NULL;
    }
    node(int val, node *l, node *r) {
        this->val = val, this->l = l, this->r = r;
    }
    node* insert(int l, int r, int x);
};
node *id;
node *root[MAXN];

node* node::insert(int l, int r, int x) {
    if(x < l || x > r) {
        return this;
    } else if(l == r) {
        return new node(this->val+1, id, id);
    }
    int mid = (l + r) >> 1;
    return new node(this->val+1, this->l->insert(l, mid, x), this->r->insert(mid+1, r, x));
}

int n, arr[MAXN], last_seen[MAXN], pr[MAXN];

int query(node *a, node *b, int ql, int qr, int l = 0, int r = n) { // return count of elements with prev(i) < ql
    if(r < ql)  return a->val - b->val;
    int mid = (l + r) >> 1, res = 0;
    res += query(a->l, b->l, ql, qr, l, mid);
    if(ql - 1 > mid) {
        res += query(a->r, b->r, ql, qr, mid+1, r);
    }
    return res;
}

int main() {
    id = new node(0, NULL, NULL);
    id->l = id, id->r = id;
    int t, q, l, r;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:\n", tc);
        scanf("%d %d", &n, &q);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &arr[i]);
            pr[i] = last_seen[arr[i]];
            last_seen[arr[i]] = i;
        }
        root[0] = id;
        for(int i = 1; i <= n; i++) {
            root[i] = root[i-1]->insert(0, n, pr[i]);
        }
        while(q--) {
            scanf("%d %d", &l, &r);
            printf("%d\n", query(root[r], root[l-1], l, r));
        }
    }
    return 0;
}
