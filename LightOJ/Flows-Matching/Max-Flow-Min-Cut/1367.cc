#include <bits/stdc++.h>
#define gc getchar_unlocked
using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

const int MAXN = 209;
const int INF = 1e8;

struct Dinic {
    static const int MAXN = 1000, INF = 1e9;
    struct edge {
        int a, b, cap, flow, low;
        edge(int a, int b, int flow, int cap, int l) : a(a), b(b), cap(cap), flow(flow), low(l) { }
    };
    int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
    vector<edge> e;
    vector<int> g[MAXN];
    //takes in number of nodes source and sink
    Dinic(int a, int b, int c): n(a), s(b), t(c) {	}
    void add_edge (int a, int b, int cap) {
        edge e1 = edge(a, b, 0, cap, -1);
        edge e2 = edge(b, a, 0, 0, -1);
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
int n, m, V, sc, sink;
int demand[MAXN];

int flow[MAXN][MAXN];

void input() {
    int a, b, l, cap;
    scanint(n), scanint(m);
    int V = n + 2, sc = 0, sink = n + 1;
    for(int i = 0; i < V; i++) demand[i] = 0;
    Dinic tester(V, sc, sink);
    vector<Dinic::edge> edges;
    int sum = 0;
    while(m--) {
        scanint(a), scanint(b), scanint(l), scanint(cap);
        tester.add_edge(a, b, cap - l);
        edges.push_back(Dinic::edge(a, b, 0, cap, l));
        demand[a] += l, demand[b] -= l;
    }
    tester.add_edge(n, 1, INF);
    demand[1] = demand[n] = 0;
    for(int i = 2; i < n; i++) sum += demand[i];
    if(sum > 0) {
        demand[n] = -sum;
        tester.add_edge(n, sink, INF);
    } else {
        demand[1] = -sum;
        tester.add_edge(sc, 1, INF);
    }
    for(int i = 1; i <= n; i++) {
        if(demand[i] > 0) {
            tester.add_edge(sc, i, demand[i]);
        } else if(demand[i] < 0) {
            tester.add_edge(i, sink, -demand[i]);
        }
    }
    int f = tester.dinic();
    bool flag = true;
    vector<Dinic::edge> &e = tester.e;
    for(int i = 0; i < e.size(); i++) {
        if(e[i].a == sc and e[i].flow < - demand[e[i].b] and e[i].b != 1) {
            flag = false;
            break;
        } else if(e[i].b == sink and e[i].flow < demand[e[i].a] and e[i].a != n) {
            flag = false;
            break;
        }
        flow[e[i].a][e[i].b] = e[i].flow;
        if(e[i].a == 1 and e[i].b == n) flow[e[i].a][e[i].b] *= -1;
    }
    if(flag == false) {
        printf(" no\n");
        return ;
    }
    printf(" yes\n");
    for(int i = 0; i < edges.size(); i++) {
        printf("%d\n", edges[i].low + flow[edges[i].a][edges[i].b]);
    }
}

int main() {
    int t;
    scanint(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:", tc);
        input();
    }
    return 0;
}
