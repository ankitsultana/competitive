/* Author: Ankit Sultana
 * Problem id: 1262
 * * * * * * * * * */
#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#define MAXN 222
#define F first
#define S second
#define INF 1000111222

using namespace std;
int answer[MAXN][MAXN];
pair<int, int> cd[MAXN][MAXN];

map<pair<int, int>, pair<int, int> > rev_map;


class Dinic{
	private:
		struct edge {
			int a, b, cap, flow;
		};
		int n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
		vector<edge> e;
		vector<int> g[MAXN];
	public:
		void solve(int k) {
			for(int i = 0; i < e.size(); i++) {
				edge elem = e[i];
				if(elem.a >= 1 && elem.a <= k && elem.b > k && elem.b <= 2*k) {
					pair<int, int> temp = rev_map[make_pair(elem.a, elem.b)];
					answer[temp.F][temp.S] = elem.flow + 1;
				}
			}
		}
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

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cout << "Case " << tc << ":\n";
		rev_map.clear();
		int no_rows, no_cols, k, sc, n, sink;
		cin >> no_rows >> no_cols;
		k = no_rows + no_cols - 1;
		n = 2 + k*2;
		sc = 0, sink = n-1;
		Dinic tester(n, sc, sink);
		/* Create cd */
		int base = 0;
		for(int r = 1; r <= no_rows; r++) {
			for(int c = 1; c <= no_cols; c++) {
				cd[r][c].F = base + c;
			}
			for(int c = no_cols; c > 0; c--) {
				cd[r][c].S = base + (no_cols - c + 1);
			}
			for(int c = 1; c <= no_cols; c++) {
				int one = cd[r][c].F, two = cd[r][c].S + k;
				rev_map[make_pair(one, two)] = make_pair(r, c);
				tester.add_edge(one, two, 99);
			}
			base++;
		}
		/* Done */
		int a, cnt = 0;
		for(int i = 1; i <= k; i++) {
			cin >> a;
			if(i > max(no_cols, no_rows)) cnt--;
			else            cnt++;
			cnt = min(cnt, min(no_rows, no_cols));
			a -= cnt;
			tester.add_edge(sc, i, a);
		}
		cnt = 0;
		for(int i = 1; i <= k; i++) {
			cin >> a;
			if(i > max(no_rows, no_cols)) cnt--;
			else                          cnt++;
			cnt = min(cnt, min(no_cols, no_rows));
			a -= cnt;
			tester.add_edge(i+k, sink, a);
		}
		a = tester.dinic();
		tester.solve(k);
		for(int i = 1; i <= no_rows; i++) {
			for(int j = 1; j <= no_cols; j++) {
				cout << answer[i][j];
				if(j != no_cols)
					cout << ' ';
			} cout << '\n';
		}
	}
	return 0;
}
