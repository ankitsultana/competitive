/* Author: Ankit Sultana
 * Problem id: 1034
 * * * * * * * * * */
#include <iostream>
#include <vector>
#define MAXN 10003

using namespace std;
int n;
int indegree[MAXN];

/* SCC */
vector<int> rev_g[MAXN], adj[MAXN];
// finv[i] returns the i-th vertex
int pool = 0, finv[MAXN], comp[MAXN], scc_cnt;

void DFS1(int r, bool vis[]) {
	if(vis[r])	return ;
	vis[r] = true;
	int size = rev_g[r].size();
	for(int i = 0; i < size; i++) {
		if(vis[rev_g[r][i]])	continue;  
		DFS1(rev_g[r][i], vis);
	}
	finv[++pool] = r;
}
void DFS2(int r, bool vis[], const int &leader) {
	if(vis[r])	return ;  
	vis[r] = true;
	comp[r] = scc_cnt;
	int size = int(adj[r].size());
	for(int i = 0; i < size; i++) {
		if(vis[adj[r][i]])	continue;  
		DFS2(adj[r][i], vis, leader);
	}
}
void init() {
	for(int i = 0; i <= n; i++) {
		adj[i].clear();
		rev_g[i].clear();
		finv[i] = 0, comp[i] = 0;
		indegree[i] = 0;
	}
}
void solve() {
	bool vis[MAXN] = {false}, visited[MAXN] = {false};
	pool = 0, scc_cnt = 0;
	for(int i = 1; i <= n; i++) {
		if(vis[i])	continue;
		DFS1(i, vis);
	}
	for(int i = n; i > 0; i--) {
		if(visited[finv[i]])	continue;  
		scc_cnt++;
		DFS2(finv[i], visited, finv[i]);
	}
}
/* End SCC */

int main() {
	ios_base::sync_with_stdio(false);
	int t, m, a, b;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n >> m;
		init();
		while(m--) {
			cin >> a >> b;  
			adj[a].push_back(b);
			rev_g[b].push_back(a);
		}
		solve();
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < adj[i].size(); j++) {
				int elem = adj[i][j];  
				if(comp[elem] == comp[i])	continue;
				else {
					indegree[comp[elem]]++;
				}
			}
		}
		int res = 0;
		for(int i = 1; i <= scc_cnt; i++) {
			if(indegree[i] == 0) {
				res++;
			}
		}
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
