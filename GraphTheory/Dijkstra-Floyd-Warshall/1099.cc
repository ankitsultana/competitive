/* Author: Ankit Sultana
 * Problem id: 1099
 * * * * * * * * * */
#include <iostream>
#include <queue>
#include <vector>
#define INF 1<<28
#define F first
#define S second
#define MAXN 5003

using namespace std;
typedef pair<int, int> data;
int n;
int dp[MAXN];
int vis[MAXN];
vector<data> adj[MAXN];

void init() {
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
        dp[i] = INF;
        vis[i] = 0;
    }
}

int dijk() {
    priority_queue<data, vector<data>, greater<data> > q;
    q.push(make_pair(0, 1));
    while(q.size()) {
        data f = q.top();
        int v = f.S, w = f.F;
        // cout << v << endl;
        q.pop();
        if(vis[v] == 0) {
            dp[v] = w;
            vis[v] = 1;
        } else if(vis[v] == 1 && dp[v] < w) {
            dp[v] = w;
            vis[v] = 2;
        } else {
            continue;
        }
        if(v == n && vis[v] == 2) {
            return dp[v];
        }
        for(int i = 0; i < adj[v].size(); i++) {
            int elem = adj[v][i].S, edge_wt = adj[v][i].F;
            if(vis[elem] == 2) {
                continue;
            } else if(vis[elem] == 1 && dp[elem] < dp[v] + edge_wt) {
                q.push(make_pair(dp[v] + edge_wt, elem));
            } else if(vis[elem] == 0) {
                q.push(make_pair(dp[v] + edge_wt, elem));
            }
        }
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        int e, a, b, w;
        cin >> n >> e;
        init();
        while(e--) {
            cin >> a >> b >> w;
            adj[a].push_back(make_pair(w, b));
            adj[b].push_back(make_pair(w, a));
        }
        cout << "Case " << tc << ": " << dijk() << "\n";
    }
    return 0;
}
