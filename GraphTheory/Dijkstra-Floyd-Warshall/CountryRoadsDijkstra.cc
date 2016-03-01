/* Author: Ankit Sultana
 * Problem id: 1002
 * * * * * * * * * */
#include <iostream>
#include <stdio.h>
#include <vector>
#define MAXN 504
#define PSIZE 100000
#define INF 1<<28
#define gc getchar_unlocked
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x; }

template<typename T, typename type_c = std::less<T> >
struct heap {
	type_c compare;
	heap() : sz(0) {
		compare = type_c();
	}
	T arr[PSIZE];
	size_t sz;
	inline size_t size()    { return sz;      }
	inline int LEFT(int i)	{ return i*2;     }
	inline int RIGHT(int i) { return i*2+1;   }
	inline bool empty()     { return sz == 0; }
	inline T top()          { return arr[1];  }
	void heapify(int i) {
		int smallest;
		while(i <= sz/2) {
			smallest = i;
			if(compare(arr[LEFT(i)], arr[i]))
				smallest = LEFT(i);
			if(RIGHT(i) <= sz && compare(arr[RIGHT(i)], arr[smallest]))
				smallest = RIGHT(i);
			if(smallest == i)	break;
			std::swap(arr[i], arr[smallest]);
			i = smallest;
		}
	}
	void bubble_up(int i) {
		while(i > 1) {
			if(compare(arr[i], arr[i/2])) {
				std::swap(arr[i], arr[i/2]);
				i /= 2;
			} else {
				break;  
			}
		}
	}
	void insert(T val) {
		if(sz >= PSIZE)	throw "Size of Heap Exceeded";
		arr[++sz] = val;
		bubble_up(sz);
	}
	void pop() {
		std::swap(arr[sz], arr[1]);
		sz--;
		heapify(1);
	}
};

template<typename T, typename type_c = std::less<T> >
struct priority_queue : heap<T, type_c> {
	int pool;
	priority_queue() : pool(0) { }
	inline T front() {
		return this->top();  
	}
	void push(T val) {
		val.first.second = ++pool;
		this->insert(val);
	}
};
using namespace std;
vector<pair<int, int> > adj[MAXN];

int answer[MAXN];
void dijk(int a) {
	priority_queue<pair<pair<int, int>, int>  > q;
	bool vis[MAXN] = {false};
	q.push(make_pair(make_pair(0, 0), a));
	while(!q.empty()) {
		pair<pair<int, int>, int> f = q.top();
		q.pop();
		if(vis[f.second])	continue;
		vis[f.second] = true;
		answer[f.second] = min(f.first.first, answer[f.second]);
		for(vector<pair<int, int> >::iterator it = adj[f.second].begin(); it != adj[f.second].end(); it++) {
			if(!vis[it->second]) {
				q.push(make_pair(make_pair(max(f.first.first, it->first), 0), it->second));
			}
		}
	}
}

int mat[MAXN][MAXN];
int main() {
	int t, n, a, b, w, pain, m;
	scanint(t);
	for(int tc = 1; tc <= t; tc++) {
		printf("Case %d:\n", tc);
		scanint(n), scanint(m);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++)
				mat[i][j] = INF;
			adj[i].clear();
			answer[i] = INF;
		}
		while(m--) {
			scanint(a), scanint(b), scanint(w);
			mat[a][b] = min(mat[a][b], w); 
			mat[b][a] = mat[a][b];
			adj[a].push_back(make_pair(w, b));
			adj[b].push_back(make_pair(w, a));
		}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(mat[i][j] < INF) {
					adj[i].push_back(make_pair(mat[i][j], j));
				}
		scanint(pain);
		dijk(pain);
		for(int i = 0; i < n; i++) {
			if(answer[i] == INF) {
				printf("Impossible\n");
			} else {
				printf("%d\n", answer[i]);
			}
		}
	}
	return 0;
}
