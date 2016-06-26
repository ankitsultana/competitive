/* Author: Ankit Sultana
 * Problem id: 1405
 * * * * * * * * * */
#include <iostream>
#include <map>
#include <cassert>
#include <vector>
#include <cstring>
#define MAXN 20008
#define INF 1<<20
using namespace std;

string grid[MAXN];
int no_rows, no_cols, in[MAXN*4], out[MAXN*4];

bool valid(int i, int j) {
	return i >= 0 && i < no_rows && j >= 0 && j < no_cols;
}

inline int ENCODE(int i, int j) {
	return i * no_cols + j;
}

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
			// cout << "ADDING: " << a << ' ' << b << ' ' << cap << endl;
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
		int sink, sc, num_conv = 0, n;
		cin >> no_rows >> no_cols;
		n = 2 * no_rows * no_cols + 2;
		sc = n - 2, sink = n - 1;
		Dinic tester(n, sc, sink);
		for(int i = 0; i < no_rows * no_cols; i++) {
			in[i] = i;
			out[i] = i + no_rows * no_cols;
			tester.add_edge(in[i], out[i], 1);
		}
		for(int i = 0; i < no_rows; i++) {
			cin >> grid[i];
			for(int j = 0; j < no_cols; j++) {
				if(grid[i][j] == '*') {
					tester.add_edge(sc, in[ENCODE(i,j)], 1);
					num_conv++;
				}
			}
		}
		for(int i = 0; i < no_rows; i++) {
			for(int j = 0; j < no_cols; j++) {
				if(valid(i-1, j)) {
					tester.add_edge(out[ENCODE(i,j)], in[ENCODE(i-1,j)], 1);
				}
				if(valid(i, j-1))
					tester.add_edge(out[ENCODE(i,j)], in[ENCODE(i,j-1)], 1);
				if(valid(i+1, j))
					tester.add_edge(out[ENCODE(i,j)], in[ENCODE(i+1,j)], 1);
				if(valid(i, j+1))
					tester.add_edge(out[ENCODE(i,j)], in[ENCODE(i,j+1)], 1);
				if(i == 0 || i == no_rows-1 || j == 0 || j == no_cols-1) {
					tester.add_edge(out[ENCODE(i,j)], sink, 1);
				}
			}
		}
		string answer = tester.dinic() == num_conv?"yes": "no";
		cout << "Case " << tc << ": " << answer << '\n';
	}
	return 0;
}
