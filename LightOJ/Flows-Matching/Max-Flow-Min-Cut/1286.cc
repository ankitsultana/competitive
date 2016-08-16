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

const int MAXN = 203;
const int INF = 1 << 28;
int num_e, num_i;
int cost[MAXN];

int main() {
    int t, temp;
    scanint(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        scanint(num_e), scanint(num_i);
        int sum = 0;
        int V = num_e + num_i + 2, sc, sink;
        sc = 0, sink = V - 1;
        Dinic tester(V, sc, sink);
        for(int i = 1; i <= num_e; i++) {
            scanint(temp);
            sum += temp;
            tester.add_edge(sc, i, temp);
        }
        for(int i = num_e + 1; i <= num_e + num_i; i++) {
            scanint(temp);
            cost[i-num_e] = temp;
            tester.add_edge(i, sink, temp);
        }
        for(int i = 1; i <= num_e; i++) {
            int q;
            scanint(q);
            while(q--) {
                scanint(temp);
                tester.add_edge(i, temp + num_e, INF);
            }
        }
        printf("%d\n", sum - tester.dinic());
    }
    return 0;
}
