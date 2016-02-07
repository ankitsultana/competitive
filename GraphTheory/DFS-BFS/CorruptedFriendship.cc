/* Author: Ankit Sultana
 * Problem id: 1357
 * * * * * * * * * */
#include <iostream>
#include <vector>
#define PB push_back
#define LL long long
#define MAXN 100003

using namespace std;
int n;
vector<int> adj[MAXN];
int subtree[MAXN];
LL res;

void DFS(int r = 1, int p = -1) {
	int elem;
	subtree[r] = 1;
	for(int i = 0; i < adj[r].size(); i++) {
		elem = adj[r][i];
		if(elem == p)	continue;
		DFS(elem, r);
		subtree[r] += subtree[elem];
	}
	int temp = subtree[r] - 1;
	for(int i = 0; i < adj[r].size(); i++) {
		elem = adj[r][i];  
		if(elem == p)	continue;
		temp -= subtree[elem];
		res += (LL)subtree[elem] * temp;
	}
}

void cleanup() {
	res = 0;
	for(int i = 1; i <= n; i++)
		adj[i].clear(), subtree[i] = 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	int a, b, t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		for(int i = 1; i < n; i++) {
			cin >> a >> b;
			adj[a].PB(b), adj[b].PB(a);
		}
		DFS();
		cout << "Case " << tc << ": " << n - 1 << ' ' << res << '\n';  
		cleanup();
	}
	return 0;
}
