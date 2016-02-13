/* Author: Ankit Sultana
 * Problem id: 1417
 * Comment: Kind of a mess, was feeling sleepy :P
 * * * * * * * * * */
#include <iostream>
#include <queue>
#include <cassert>
#include <vector>
#define MAXN 50003
#define what_is(x) cout<<#x<<" is "<<x<<'\n'

using namespace std;
int n, indegree[MAXN];
int lite[MAXN];
int dp[MAXN];

/* SCC */
vector<int> rev_g[MAXN], adj[MAXN], next_node[MAXN];
// finv[i] returns the i-th vertex
int pool = 0, finv[MAXN], comp[MAXN], scc_cnt;
int strength[MAXN];

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
	lite[scc_cnt] = min(lite[scc_cnt], r);
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
		next_node[i].clear();
		strength[i] = 0;
		lite[i] = 0;
		dp[i] = 0;
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
		lite[scc_cnt] = finv[i];
		DFS2(finv[i], visited, finv[i]);
	}
}
/* End SCC */

int main() {
	ios_base::sync_with_stdio(false);
	int t, m, a, b;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		init();
		for(int i = 0; i < n; i++) {
			cin >> a >> b;  
			adj[a].push_back(b);
			rev_g[b].push_back(a);
		}
		solve();
		for(int i = 1; i <= n; i++) {
			strength[comp[i]]++;
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < adj[i].size(); j++) {
				if(comp[i] != comp[adj[i][0]]) {
					next_node[comp[adj[i][0]]].push_back(comp[i]);
					indegree[comp[i]]++;
				}
			}
		}
		queue<int> q;
		for(int i = 1; i <= scc_cnt; i++) {
			if(indegree[i] == 0) {
				q.push(i);  
			}
		}
		while(!q.empty()) {
			int f = q.front();
			q.pop();
			dp[f] += strength[f];
			for(int i = 0; i < next_node[f].size(); i++) {
				int elem = next_node[f][i];
				indegree[elem]--;
				assert(indegree[elem] == 0);
				q.push(elem);
				dp[elem] += dp[f];
			}
		}
		int maxim = 0;
		for(int i = 1; i <= scc_cnt; i++) {
			maxim = max(maxim, dp[i]);  
		}
		int res = 1<<28;
		for(int i = 1; i <= scc_cnt; i++) {
			if(dp[i] == maxim && res > lite[i]) {
				res = lite[i];
			}
		}
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
