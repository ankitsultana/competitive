/* Author: Ankit Sultana
 * Problem id: 1156
 * * * * * * * * * */
#include <iostream>
#include <map>
#include <cassert>
#include <vector>
#include <cstring>
#define MAXN 200
#define INF 1<<20
using namespace std;


bool debug = false;
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
			if(debug)	cout << "ADDING: (" << a << ", " << b << ", " << cap<<")\n";
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

struct stone {
	int x;
	int jump;
}stones[MAXN];

int num_stones, width, in[MAXN], out[MAXN];
bool poss(int maxim) {
	int sc = 0, sink, n;
	n = 2*num_stones - 2;
	sink = n - 1;
	Dinic tester(n, sc, sink);
	stones[sc].x = 0, stones[sink].x = width;
	for(int i = 1; i <= num_stones - 2; i++) {
		if(stones[i].x <= maxim) {
			tester.add_edge(sc, in[i], stones[i].jump);
		}
		if(width - stones[i].x <= maxim)
			tester.add_edge(out[i], sink, stones[i].jump);
		tester.add_edge(in[i], out[i], stones[i].jump);
	}
	for(int i = 1; i <= num_stones - 2; i++) {
		for(int j = i+1; j <= num_stones - 2; j++) {
			if(stones[j].x - stones[i].x <= maxim) {
				tester.add_edge(out[i], in[j], 2);
				tester.add_edge(out[j], in[i], 2);
			}
		}
	}
	if(stones[sink].x - stones[sc].x <= maxim)
		tester.add_edge(sc, sink, 2);
	return tester.dinic() > 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t, a;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cout << "Case " << tc << ": ";
		cin >> num_stones >> width;
		num_stones += 2;
		in[0] = 0, out[0] = 0;
		in[num_stones-1] = num_stones-1, out[num_stones-1] = num_stones-1;
		for(int i = 1; i <= num_stones - 2; i++) {
			char x, hyphen;
			cin >> x >> hyphen >> a;
			in[i] = i, out[i] = i+num_stones-2;
			stones[i].jump = x == 'B'?2: 1;
			stones[i].x = a;
		}
		int low = 1, upper = 1000000000, mid;
		while(low < upper) {
			mid = low + (upper - low)/2;
			if(poss(mid)) {
				upper = mid;
			} else {
				low = mid+1;
			}
		}
		cout << low << '\n';
	}
	return 0;
}
