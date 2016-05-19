/* Author: Ankit Sultana
 * Problem Name: Save the Trees (1415)
 * * * * * * * * * * */
#include <iostream>
#include <cstdio>
#include <stack>
#define LL long long
#define MAXN 200003

using namespace std;

LL type[MAXN], ht[MAXN], dp[MAXN], n, last_seen[MAXN], l_min[MAXN];

struct node {
    LL minim, uska_f, min_dp;
    bool lazy;
    void split(node &l, node &r) {
        if(lazy) {
            l.minim = l.min_dp + uska_f;
            r.minim = r.min_dp + uska_f;
            l.uska_f = uska_f;
            r.uska_f = uska_f;
            l.lazy = true;
            r.lazy = true;
        }
        lazy = false;
    }
    void merge(node &l, node &r) {
        minim = min(l.minim, r.minim);
        min_dp = min(l.min_dp, r.min_dp);
    }
}tree[5*MAXN], id;

void build_tree(LL root = 1, LL l = 0, LL r = n) {
    tree[root].minim = 0, tree[root].uska_f = 0, tree[root].min_dp = 0;
    tree[root].lazy = false;
    if(l == r) {
        return ;
    }
    build_tree(root*2, l, (l+r)>>1);
    build_tree(root*2+1, ((l+r)>>1)+1, r);
}

void update(LL ql, LL qr, LL x, LL root = 1, LL l = 0, LL r = n) {
    if(ql <= l && qr >= r) {
        tree[root].lazy = true;
        tree[root].uska_f = x;
        tree[root].minim = tree[root].min_dp + x;
        return ;
    } else if(ql > r || qr < l) {
        return ;
    }
    LL mid = (l + r) >> 1;
    tree[root].split(tree[root*2], tree[root*2+1]);
    update(ql, qr, x, root*2, l, mid);
    update(ql, qr, x, root*2+1, mid+1, r);
    tree[root].merge(tree[root*2], tree[root*2+1]);
}

node query(LL ql, LL qr, LL root = 1, LL l = 0, LL r = n) {
    if(ql <= l && qr >= r) {
        return tree[root];
    } else if(ql > r || qr < l) {
        return id;
    }
    LL mid = (l + r) >> 1;
    tree[root].split(tree[root*2], tree[root*2+1]);
    node res = id, one = id, two = id;
    one = query(ql, qr, root*2, l, mid);
    two = query(ql, qr, root*2+1, mid+1, r);
    tree[root].merge(tree[root*2], tree[root*2+1]);
    res.merge(one, two);
    return res;
}

void setter(LL idx, LL dp_val, LL f_val, LL root = 1, LL l = 0, LL r = n) {
    if(l == r) {
        tree[root].minim = dp_val + f_val;
        tree[root].min_dp = dp_val;
        tree[root].uska_f = f_val;
        return ;
    }
    LL mid = (l + r) >> 1;
    tree[root].split(tree[root*2], tree[root*2+1]);
    if(idx > mid)
        setter(idx, dp_val, f_val, root*2+1, mid+1, r);
    else
        setter(idx, dp_val, f_val, root*2, l, mid);
    tree[root].merge(tree[root*2], tree[root*2+1]);
}

int main() {
    int t;
#ifdef local
    freopen("1", "rb", stdin);
#endif
    scanf("%d", &t);
    id.minim = id.min_dp = id.uska_f = 1ll<<60;
    for(int tc = 1; tc <= t; tc++) {
        scanf("%lld", &n);
        for(LL i = 1; i <= n; i++) {
            scanf("%lld %lld", &type[i], &ht[i]);
            last_seen[type[i]] = -1;
        }
        stack<LL> s;
        for(LL i = 1; i <= n; i++) {
            while(s.size() && ht[s.top()] <= ht[i]) {
                s.pop();
            }
            if(s.empty()) {
                l_min[i] = 0;
            } else {
                l_min[i] = s.top();
            }
            s.push(i);
        }
        build_tree();
        LL l = 0;
        setter(0, 0, ht[1]);
        for(LL i = 1; i <= n; i++) {
            if(l_min[i] <= i-1)
                update(l_min[i], i-1, ht[i]);
            l = max(l, last_seen[type[i]]);
            dp[i] = query(l, i-1).minim;
            setter(i, dp[i], ht[i+1]);
            last_seen[type[i]] = i;
        }
        printf("Case %d: %lld\n", tc, dp[n]);
    }
    return 0;
}
