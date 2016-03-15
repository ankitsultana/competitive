/* Author: Ankit Sultana
 * Problem id: 1029
 * * * * * * * * * */
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#define LL long long
#define MAXN 103

using namespace std;

template<typename T>
T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }

int n, Rank[MAXN], P[MAXN];

struct edge {
	int a, b, low, high, wt;
	bool operator<(const edge &other) const {
		return wt < other.wt;
	}
	void insert(int x) {
		if(low == -1) {
			low = x, high = x;
		} else if(x < low) {
			low = x;
		} else if(x > high) {
			high = x;
		}
	}
	void init() {
		low = -1, high = -1, wt = -1;
	}
};

struct UnionFind {
	int V;
	UnionFind(int V) {
		this->V = V;
		for(int i = 0; i < V; i++)
			Rank[i] = 1, P[i] = i;
	}
	int find_root(int x) { return x == P[x]?x: P[x] = find_root(P[x]); }
	void Union(int i, int j) {
		int iroot = find_root(i), jroot = find_root(j);
		if(iroot == jroot)	return ;
		if(Rank[iroot] >= Rank[jroot]) {
			P[jroot] = iroot;
			Rank[iroot] += Rank[jroot];
		} else {
			P[iroot] = jroot;
			Rank[jroot] += Rank[iroot];
		}
	}
	bool cycle(int i, int j) {
		return find_root(i) == find_root(j);
	}
};

map<int, map<int, int> > cache;

int main() {
	ios_base::sync_with_stdio(false);
	int t, a, b, c;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cache.clear();
		cout << "Case " << tc << ": ";
		vector<edge> e;
		cin >> n;
		edge temp;
		while(cin >> a >> b >> c) {
			if(a + b + c == 0)	break;
			if(a > b)	swap(a, b);
			if(cache[a].count(b)) {
				e[cache[a][b]].insert(c);
			} else {
				temp.init();
				temp.a = a, temp.b = b, temp.insert(c);
				e.push_back(temp);
				cache[a][b] = e.size()-1;
			}
		}
		int res_one = 0, res_two = 0;
		UnionFind one(n+1);
		for(int i = 0; i < e.size(); i++)	e[i].wt = e[i].low;
		sort(e.begin(), e.end());
		for(int i = 0; i < e.size(); i++) {
			if(not one.cycle(e[i].a, e[i].b)) {
				one.Union(e[i].a, e[i].b);
				res_one += e[i].wt;
			}
		}
		for(int i = 0; i < e.size(); i++)	e[i].wt = -e[i].high;
		sort(e.begin(), e.end());
		UnionFind two(n+1);
		for(int i = 0; i < e.size(); i++) {
			if(not two.cycle(e[i].a, e[i].b)) {
				two.Union(e[i].a, e[i].b);
				res_two += e[i].wt;
			}
		}
		res_two = -res_two;
		if((res_one + res_two) % 2 == 0) {
			cout << (res_one + res_two)/2 << '\n';
		} else {
			cout << res_one + res_two << '/' << 2 << '\n';
		}
	}
	return 0;
}
