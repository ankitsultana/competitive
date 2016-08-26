#include <bits/stdc++.h>
#define gc getchar_unlocked
using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

class Dinic {
static const int MAXN = 1000, INF = 1e9;
private:
    struct edge {
        int a, b, cap, flow;
    };
    int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
    vector<edge> e;
    vector<int> g[MAXN];
public:
    //takes in number of nodes source and sink
    Dinic(int a, int b, int c): n(a), s(b), t(c) {	}
    void add_edge (int a, int b, int cap) {
        edge e1 = { a, b, cap, 0 };
        edge e2 = { b, a, 0, 0 };
        g[a].push_back ((int) e.size());
        e.push_back (e1);
        g[b].push_back ((int) e.size());
        e.push_back (e2);
    }
    bool bfs() {
        int qh=0, qt=0;
        q[qt++] = s;
        memset (d, -1, n * sizeof d[0]);
        d[s] = 0;
        while (qh < qt && d[t] == -1) {
            int v = q[qh++];
            for (size_t i=0; i<g[v].size(); ++i) {
                int id = g[v][i],
                    to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }
    int dfs (int v, int flow) {
        if (!flow)  return 0;
        if (v == t)  return flow;
        for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1)  continue;
            int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    int dinic() {
        int flow = 0;
        for (;;) {
            if (!bfs())  break;
            memset (ptr, 0, n * sizeof ptr[0]);
            while (int pushed = dfs (s, INF))
                flow += pushed;
        }
        return flow;
    }
};

int t, n, k, E;

struct edge {
    int a, b, cap;
} es[100003];

bool check(int x) {
    int V = 2*n + 2, sc = 0, sink = V - 1;
    Dinic tester(V, sc, sink);
    for(int i = 1; i <= n; i++) tester.add_edge(i, i + n, 1);
    for(int i = 0; i < E; i++) {
        if(es[i].cap <= x) {
            if(es[i].a == 0) {
                tester.add_edge(sc, es[i].b == n + 1 ? sink : es[i].b, 1);
            } else if(es[i].b == n + 1) {
                if(es[i].a == 0)
                    tester.add_edge(sc, sink, 1);
                else
                    tester.add_edge(es[i].a + n, sink, 1);
            } else {
                tester.add_edge(es[i].a + n, es[i].b, 1);
            }
        }
    }
    return tester.dinic() >= k;
}

int main() {
    scanint(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        scanint(n), scanint(E);
        for(int i = 0; i < E; i++) {
            scanint(es[i].a), scanint(es[i].b), scanint(es[i].cap);
            if(es[i].a > es[i].b) swap(es[i].a, es[i].b);
        }
        scanint(k);
        int lower = 0, upper = 1e5 + 5, mid;
        while(lower < upper) {
            mid = (lower + upper) / 2;
            if(check(mid)) {
                upper = mid;
            } else {
                lower = mid + 1;
            }
        }
        if(check(lower) == false) {
            printf("no solution\n");
        } else {
            printf("%d\n", lower);
        }
    }
    return 0;
}
