/* Author: Ankit Sultana
 * Problem id: 1155
 * * * * * * * * * */
#ifdef __APPLE__
	#include <iostream>
#endif
#include <stdio.h>
#include <cassert>
#include <vector>
#include <cstring>
#define MAXN 403
#define INF 1<<25
using namespace std;

class Dinic{
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
int reg[MAXN];
int main() {
	int t;
	scanf("%d", &t);
	for(int tc = 1; tc <= t; tc++) {
		printf("Case %d: ", tc);
		int n, a, b, c, m;
		scanf("%d", &n);
		Dinic tester(3*n+2, 0, 3*n+1);
		for(int i = 1; i <= n; i++) {
			scanf("%d", &reg[i]);
			tester.add_edge(i, i+n, reg[i]);
			tester.add_edge(i+n, i+2*n, reg[i]);
		}
		scanf("%d", &m);
		while(m--) {
			scanf("%d %d %d", &a, &b, &c);  
			tester.add_edge(a+2*n, b, c);
		}
		int c1, c2, temp;
		scanf("%d %d", &c1, &c2);
		while(c1--) {
			scanf("%d", &temp);
			tester.add_edge(0, temp, INF);
		}
		while(c2--) {
			scanf("%d", &temp);
			tester.add_edge(temp+2*n, 3*n+1, INF);
		}
		printf("%d\n", tester.dinic());
	}
	return 0;
}
