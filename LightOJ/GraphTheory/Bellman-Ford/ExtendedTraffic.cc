#include <iostream>
#include <vector>
#define INF 1<<28
#define MAXN 203

using namespace std;

int dp[MAXN], n, busy[MAXN];
vector<int> adj[MAXN];

inline int cubed(int i, int j) {
    return (busy[j] - busy[i]) * (busy[j] - busy[i]) * (busy[j] - busy[i]);
}

void init() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        adj[i].clear();
        dp[i] = INF;
        cin >> busy[i];
    }
    int m, a, b;
    cin >> m;
    while(m--) {
        cin >> a >> b;
        adj[a].push_back(b);
    }
}

void bellmanford() {
    init();
    dp[1] = 0;
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 0; k < adj[j].size(); k++) {
                int other = adj[j][k];
                if(dp[j] < INF) {
                    dp[other] = min(dp[other], dp[j] + cubed(j, other));
                }
            }
        }
    }
    int q, x;
    cin >> q;
    while(q--) {
        cin >> x;
        if(dp[x] == INF or dp[x] < 3) {
            cout << "?\n";
        } else {
            cout << dp[x] << '\n';
        }
    }
}

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ":\n";
        bellmanford();
    }
    return 0;
}
