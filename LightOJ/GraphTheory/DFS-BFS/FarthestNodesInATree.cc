/* Author: Ankit Sultana
 * Problem id: 1094
 * * * * * * * * * */
#include <iostream>
#include <stdio.h>
#include <vector>
#define LL long long
#define MAXN 30003
using namespace std;

int n;
vector<int> adj[MAXN];
vector<int> wt[MAXN];
LL dp[MAXN][2];

void DFS(int root = 0, int prev = -1) {
	dp[root][0] = (dp[root][1] = 0);
	LL maxim = 0, s_maxim = 0;
	for(int i = 0; i < adj[root].size(); i++) {
		int elem = adj[root][i];
		if(elem == prev)	continue;
		DFS(elem, root);
		if(dp[elem][1] + wt[root][i] > maxim) {
			s_maxim = maxim;
			maxim = dp[elem][1] + wt[root][i];
		} else if(dp[elem][1] + wt[root][i] > s_maxim) {
			s_maxim = dp[elem][1] + wt[root][i];  
		}
	}
	dp[root][1] = maxim;
	dp[root][0] = maxim + s_maxim;
}

int main() {
	int t;
	scanf("%d", &t);
	for(int tc = 1; tc <= t; tc++) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			adj[i].clear();  
			wt[i].clear();
		}
		int a, b, w;
		for(int i = 1; i < n; i++) {
			scanf("%d %d %d", &a, &b, &w);
			adj[a].push_back(b);
			wt[a].push_back(w);
			adj[b].push_back(a);
			wt[b].push_back(w);
		}
		DFS();
		LL res = 0;
		for(int i = 0; i < n; i++)
			res = max(res, dp[i][0]);
		printf("Case %d: %lld\n", tc, res);
	}
	return 0;
}
