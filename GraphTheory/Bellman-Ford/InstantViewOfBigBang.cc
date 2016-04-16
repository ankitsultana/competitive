/* AUthor: Ankit Sultana
 * ID: 1108
 * * * * * * * * * * */
#include <iostream>
#include <vector>
#include <iterator>
#include <set>
#define INF 1<<28
#define MAXN 1003

using namespace std;
vector<int> adj[MAXN];
vector<int> cycle;
vector<int> wt[MAXN];
int dp[MAXN];
bool vis[MAXN];
set<int> result;
int n, m;

void init() {
    cin >> n >> m;
    for(int i = 0; i <= n; i++) {
        adj[i].clear();
        wt[i].clear();
        vis[i] = false;
        dp[i] = INF;
    }
    cycle.clear();
    result.clear();
    int a, b, c;
    while(m--) {
        cin >> a >> b >> c;
        adj[++b].push_back(++a);
        wt[b].push_back(c);
    }
    for(int i = 1; i <= n; i++) {
        adj[0].push_back(i);
        wt[0].push_back(0);
    }
}

void dfs(int root) {
    if(vis[root])   return ;
    vis[root] = true;
    result.insert(root);
    for(int i = 0; i < adj[root].size(); i++) {
        int other = adj[root][i];
        if(!vis[other]) dfs(other);
    }
}

void bellmanford() {
    init();
    dp[0] = 0;
    for(int i = 0; i <= n; i++) {
        for(int k = 0; k <= n; k++) {
            for(int j = 0; j < adj[k].size(); j++) {
                int other = adj[k][j];
                if(dp[k] != INF && dp[other] > dp[k] + wt[k][j]) {
                    if(i == n)
                        cycle.push_back(other);
                    dp[other] = dp[k] + wt[k][j];
                }
            }
        }
    }
    for(int i = 0; i < cycle.size(); i++) {
        if(vis[cycle[i]]) continue;
        dfs(cycle[i]);
    }
}

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        bellmanford();
        if(result.empty()) {
            cout << "impossible\n";
        } else {
            for(set<int>::iterator it = result.begin(); it != result.end(); it++) {
                if(*it == 0)    continue;
                cout << *it - 1;
                if(++it != result.end())
                    cout << ' ';
                it--;
            } cout << '\n';
        }
    }
    return 0;
}
