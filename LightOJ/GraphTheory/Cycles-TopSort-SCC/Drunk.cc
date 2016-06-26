/* Author: Ankit Sultana
 * Problem id: 1003
 * * * * * * * * * */
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#define MAXN 20003

using namespace std;

int indegree[MAXN];
vector<int> adj[MAXN];
int main() {
	ios_base::sync_with_stdio(false);
	int t, n;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		map<string, int> idx;
		string st_a, st_b;
		int cnt = 0;
		cin >> n;
		for(int i = 0; i < n; i++) {
			cin >> st_a >> st_b;
			if(!idx.count(st_a)) {
				idx[st_a] = ++cnt;
			}
			if(!idx.count(st_b)) {
				idx[st_b] = ++cnt;
			}
			adj[idx[st_a]].push_back(idx[st_b]);
			indegree[idx[st_b]]++;
		}
		queue<int> q;
		for(int i = 1; i <= cnt; i++) {
			if(indegree[i] == 0)
				q.push(i);
		}
		int vis_cnt = 0, elem;
		while(!q.empty()) {
			int f = q.front();
			q.pop();
			vis_cnt++;
			for(int i = 0; i < adj[f].size(); i++) {
				elem = adj[f][i];
				indegree[elem]--;
				if(indegree[elem] == 0) {
					q.push(elem);
				}
			}
		}
		string answer;
		if(vis_cnt == cnt) {
			answer = "Yes\n";
		} else {
			answer = "No\n";  
		}
		cout << "Case " << tc << ": " << answer;
		// cleanup
		for(int i = 1; i <= cnt; i++) {
			adj[i].clear();  
			indegree[i] = 0;
		}
	}
	return 0;
}
