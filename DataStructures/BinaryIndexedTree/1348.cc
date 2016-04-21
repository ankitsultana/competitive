/* Author: Ankit Sultana
 * Problem Name: Aladdin and Return Journey (1348)
 * * * * * * * * * * * * * * * * * */
#ifdef __APPLE__
    #include <iostream>
#endif
#include <stdio.h>
#include <vector>
#include <algorithm>
#define LL long long
#define MAXLOGN 19
#define MAXN 30009

using namespace std;
int bitpool[20][MAXN], n, pool = 0, st[MAXN], wt[MAXN], en[MAXN], actual[MAXN];
int *bit = bitpool[0];
vector<int> adj[MAXN];

/* LCA BEGIN */
#define MAXLOGN 19
int pa[MAXN][MAXLOGN];
int depth[MAXN] = {0};

void lca_dfs(int node = 1, int prev = -1, int d = 0) {
	depth[node] = d;
	pa[node][0] = prev;
	int sz = int(adj[node].size());
	for(int i = 0; i < sz; i++) {
		if(adj[node][i] == prev)	continue;
		lca_dfs(adj[node][i], node, d+1);
	}
}
void preprocess_lca() {
	std::fill(&pa[0][0], &pa[0][0] + MAXN*MAXLOGN, -1);
	lca_dfs();
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= n; i++)
			if(pa[i][j-1] != -1) pa[i][j] = pa[pa[i][j-1]][j-1];
}
int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u,v);
	int diff = depth[u]-depth[v];
	for(int i = 0; i < MAXLOGN; i++) if((diff>>i)&1) u = pa[u][i];
	if(u == v) return u;
	for(int i = MAXLOGN-1; i > -1; i--) if(pa[u][i] != pa[v][i])
		u = pa[u][i], v= pa[v][i];
	return pa[u][0];
}
/* LCA END */

void walk(int r, int p) {
    st[r] = ++pool;
    wt[r] += wt[p];
    for(int i = 0; i < adj[r].size(); i++) {
        if(adj[r][i] == p)  continue;
        walk(adj[r][i], r);
    }
    en[r] = pool;
}
void update(int idx, int val) {
    while(idx < MAXN) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}
int query(int idx) {
    int res = 0;
    while(idx) {
        res += bit[idx];
        idx -= idx & (-idx);
    }
    return res;
}

void range_update(int u, int v, int val) {
    update(u, val);
    update(v+1, -val);
}

int main() {
    int t, a, b, opt, q;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:\n", tc);
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &wt[i]);
            actual[i] = wt[i];
        }
        for(int i = 1; i < n; i++) {
            scanf("%d %d", &a, &b);
            a++, b++;
            adj[a].push_back(b), adj[b].push_back(a);
        }
        preprocess_lca();
        walk(1, 0);
        for(int i = 1; i <= n; i++) {
            range_update(st[i], st[i], wt[i]);
        }
        scanf("%d", &q);
        pa[1][0] = 0;
        while(q--) {
            scanf("%d %d %d", &opt, &a, &b);
            if(opt) {
                a++;
                int curr = query(st[a]) - query(st[pa[a][0]]);
                range_update(st[a], en[a], b - curr);
            } else {
                a++, b++;
                int l = LCA(a, b);
                printf("%d\n", query(st[a]) + query(st[b]) - query(st[l]) - query(st[pa[l][0]]));
            }
        }
        for(int i = 1; i <= n; i++) adj[i].clear();
        pool = 0;
        bit += MAXN;
    }
    return 0;
}
