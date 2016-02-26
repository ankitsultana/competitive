/* Author: Ankit Sultana
 * Problem id: 1154
 * * * * * * * * * */
#include <iostream>
#include <cmath>
#include <map>
#include <cassert>
#include <vector>
#include <cstring>
#define LL long long
#define MAXN 309
#define INF 1<<20
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
double distance(int x1, int y1, int x2, int y2) {
	return sqrt(((LL)(x1-x2)*(LL)(x1-x2)) + ((LL)(y1-y2)*(LL)(y1-y2)));
}
struct query {
	double x, y;
	int n, m;
}queries[MAXN];
int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cout << "Case " << tc << ": ";
		int n, num_p, max_jumps, total = 0, V;
		double x, y, d;
		cin >> n >> d;
		for(int i = 0; i < n; i++) {
			cin >> x >> y >> num_p >> max_jumps;
			total += num_p;
			queries[i] = {x, y, num_p, max_jumps};
		}
		vector<int> res;
		V = 3*n+1;
		for(int i = n+1; i <= 2*n; i++) {
			Dinic tester(V, 0, i);
			for(int j = 1; j <= n; j++)
				tester.add_edge(0, j, INF), tester.add_edge(j, j + n, queries[j-1].n),
					tester.add_edge(j+n, j+2*n, queries[j-1].m);
			for(int j = 0; j < n; j++) {
				for(int k = 0; k < n; k++) {
					if(j == k)	continue;
					int one = j+2*n+1, two = k+n+1;
					if(distance(queries[j].x, queries[j].y, queries[k].x, queries[k].y) <= d) {
						tester.add_edge(one, two, queries[j].m);
					}
				}
			}
			if(tester.dinic() == total) {
				res.push_back(i-n-1);
			}
		}
		if(res.empty()) {
			cout << -1 << '\n';
		} else {
			for(int i = 0; i < res.size() - 1; i++) {
				cout << res[i] << ' ';  
			} cout << res.back() << '\n';
		}
	}
	return 0;
}
