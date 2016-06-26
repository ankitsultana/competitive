#include <cstdio>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#define F first
#define S second
#define gc getchar_unlocked
using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

typedef pair<int, int> pt;

const int MAXN = 5e4 + 3, MAXV = 5e4 + 3, INF = 1e9 + 8;
int arr[MAXN], n, dp[MAXV];
vector<pair<int, int> > adj[MAXV];
int main() {
    int q, k;
    scanint(n);
    for(int i = 0; i < n; i++) scanint(arr[i]);
    std::fill(dp, dp + arr[0], INF);
    priority_queue<pt, vector<pt>, greater<pt> > dijk;
    dijk.push(make_pair(0, 0));
    dp[0] = 0;
    while(dijk.empty() == false) {
        pt f = dijk.top();
        dijk.pop();
        int from = f.S, wt = f.F, to;
        for(int i = 1; i < n; i++) {
            to = (from + arr[i]) % arr[0];
            if(wt + arr[i] < dp[to]) {
                dp[to] = wt + arr[i];
                dijk.push(make_pair(wt + arr[i], to));
            }
        }
    }
    scanint(q);
    while(q--) {
        scanint(k);
        if(dp[k % arr[0]] != INF and dp[k % arr[0]] <= k) printf("TAK\n");
        else printf("NIE\n");
    }
    return 0;
}
