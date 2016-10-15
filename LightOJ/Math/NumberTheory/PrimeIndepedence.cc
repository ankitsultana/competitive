/* Author: Ankit Sultana
 * Problem id: 1356
 * * * * * * * * * */
#include <bits/stdc++.h>
#define gc getchar_unlocked
using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

const int MAXN = 500003;
int n, arr[int(4e4 + 4)];
int indexOf[MAXN];
vector<int> adj[int(4e4 + 4)];
bool vis[int(4e4 + 3)], is_prime[MAXN];
vector<int> primes;
int V, Rank[MAXN], P[MAXN];
bool color[MAXN];

void reset() {
    for(int i = 1; i <= n; i++) {
        indexOf[arr[i]] = 0;
        vis[i] = false;
        adj[i].clear();
        color[i] = false;
    }
}
void sieve_eratosthenes() {
	std::fill(&is_prime[0], &is_prime[0] + MAXN, true);
	is_prime[1] = false;
	for(int i = 2; i*i <= MAXN; i++){
		if(is_prime[i]){
			for(int j = i*i; j < MAXN; j += i){
				is_prime[j] = false;
			}
		}
	}
	for(int i = 2; i < MAXN; i++) {
		if(is_prime[i]) primes.push_back(i);
	}
}
class Dinic {
    static const int MAXN = 8e4 + 10, INF = 1e9;
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
int main() {
    sieve_eratosthenes();
    int t;
    scanint(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        scanint(n);
        int sc = 0, sink = 2*n + 1;
        Dinic tester(2 * n + 2, sc, sink);
        for(int i = 1; i <= n; i++) {
            scanint(arr[i]);
            indexOf[arr[i]] = i;
            tester.add_edge(sc, i, 1);
            tester.add_edge(i + n, sink, 1);
        }
        vector<pair<int, int> > e;
        for(int i = 1; i <= n; i++) {
            int id = 0, temp = arr[i], elem, cnt = 0;
            while(primes[id] * primes[id] <= temp) {
                if(temp % primes[id] == 0) {
                    elem = arr[i] / primes[id];
                    if(indexOf[elem]) {
                        e.push_back({indexOf[elem], i});
                    }
                    while(temp % primes[id] == 0) temp /= primes[id], cnt++;
                }
                id++;
            }
            if(temp > 1) {
                if(indexOf[arr[i]/temp]) {
                    elem = arr[i]/temp;
                    e.push_back({indexOf[elem], i});
                }
                cnt++;
            }
            color[i] = cnt % 2;
        }
        for(int i = 0; i < e.size(); i++) {
            pair<int, int> edge = e[i];
            if(color[edge.first]) {
                tester.add_edge(edge.first, edge.second + n, 1);
            } else {
                tester.add_edge(edge.second, edge.first + n, 1);
            }
        }
        int vc = tester.dinic();
        printf("%d\n", n - vc);
        reset();
    }
    return 0;
}
