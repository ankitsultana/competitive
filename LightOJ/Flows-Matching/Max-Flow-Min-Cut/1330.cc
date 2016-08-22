#include <bits/stdc++.h>
#define gc getchar_unlocked
using namespace std;

template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

const int MAXN = 109;
const int INF = 1e8;
int R, C, V, sc, sink;
int A[MAXN], B[MAXN];
int flow[MAXN][MAXN];
int cap[MAXN][MAXN];
int grid[MAXN][MAXN];
int d[MAXN];
int q[MAXN*MAXN];
bool vis[MAXN];

int from[MAXN];

bool bfs() {
    for(int i = 0; i < MAXN; i++) d[i] = -1, vis[i] = false, from[i] = -1;
    int q_l = 0, q_r = 0;
    q[q_r++] = sc;
    d[sc] = 0;
    while(q_l < q_r) {
        int f = q[q_l++];
        if(vis[f]) continue;
        vis[f] = true;
        for(int i = 0; i < MAXN; i++) {
            if(cap[f][i] - flow[f][i] > 0 and d[i] == -1) {
                d[i] = d[f] + 1;
                from[i] = f;
                q[q_r++] = i;
            }
        }
    }
    return d[sink] != -1;
}

int dfs(int node, int f = INF) {
    if(node == sink) return f;
    else if(!f) return 0;
    int pushed = -1;
    for(int i = 0; i < MAXN; i++) {
        if(d[i] == d[node] + 1 and cap[node][i] - flow[node][i] > 0) {
            pushed = dfs(i, min(f, cap[node][i] - flow[node][i]));
            if(pushed > 0) {
                flow[node][i] += pushed;
                flow[i][node] -= pushed;
                return pushed;
            }
        }
    }
    return -1;
}

int augment() {
    if(bfs() == false) return -1;
    int curr = sink;
    while(curr) {
        flow[from[curr]][curr] += 1;
        flow[curr][from[curr]] -= 1;
        curr = from[curr];
    }
    return 1;
}

int max_flow() {
    int res = 0, pushed;
    while(bfs()) {
        while(true) {
            pushed = dfs(sc);
            if(pushed <= 0) break;
            res += pushed;
        }
    }
    return res;
}

void solve() {
    int f = max_flow();
    bool flag = true;
    for(int i = 1; i <= R; i++)
        if(flow[sc][i] != A[i]) {
            flag = false;
            break;
        }
    for(int i = 1; i <= C; i++)
        if(flow[i + R][sink] != B[i]) {
            flag = false;
            break;
        }
    if(flag == false) {
        printf(" impossible\n");
        return ;
    }
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++) {
            if(flow[r][c + R] == 1) {
                // Try blocking flow
                flow[c + R][r] = 0;
                flow[sc][r]--, flow[c + R][sink]--;
                flow[r][sc]++, flow[sink][c + R]++;
                int a = augment();
                assert(a == -1 || a == 0 || a == 1);
                if(a == 1) {
                    grid[r][c] = 0;
                } else {
                    flow[sc][r]++, flow[c + R][sink]++;
                    flow[r][sc]--, flow[sink][c + R]--;
                    grid[r][c] = 1;
                }
            } else {
                flow[r][c + R] += 1;
                flow[c + R][r] -= 1;
                grid[r][c] = 0;
            }
        }
    }
    printf("\n");
    for(int i = 1; i <= R; i++) {
        for(int j = 1; j <= C; j++) {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

void input() {
    scanint(R), scanint(C);
    V = R + C + 2, sc = 0, sink = V - 1;
    for(int i = 1; i <= R; i++) {
        scanint(A[i]);
    }
    for(int i = 1; i <= C; i++) {
        scanint(B[i]);
    }
    for(int i = 0; i < MAXN; i++) for(int j = 0; j < MAXN; j++) flow[i][j] = cap[i][j] = 0;
    for(int i = 1; i <= R; i++) {
        cap[sc][i] = A[i];
    }
    for(int i = 1; i <= C; i++) {
        cap[i + R][sink] = B[i];
    }
    for(int i = 1; i <= R; i++) for(int j = 1; j <= C; j++)
        cap[i][j + R] = 1;
}

int main() {
    int t;
    scanint(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:", tc);
        input();
        solve();
    }
    return 0;
}
