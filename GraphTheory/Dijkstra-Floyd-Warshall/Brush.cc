/* Author: Ankit Sultana
 * Problem id: 1019
 * * * * * * * * * */
#include <iostream>
#include <vector>
template<typename T, typename Container = std::vector<T>, typename Type_c = std::less<T> >
struct heap {
	Type_c compare;
	Container arr;
	heap() : sz(0) {
		compare = Type_c();
		arr = Container();
	}
	size_t sz;
	inline size_t size()    { return sz;      }
	inline int LEFT(int i)	{ return i*2+1;   }
	inline int RIGHT(int i) { return i*2+2;   }
	inline bool empty()     { return sz == 0; }
	inline T top()          { return arr.front();  }
	void heapify(int i) {
		int smallest;
		while(sz > 0 && i < (sz-1)/2) {
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
		while(i > 0) {
			if(compare(arr[i], arr[(i-1)/2])) {
				std::swap(arr[i], arr[(i-1)/2]);
				i = (i-1)/2;
			} else {
				break;
			}
		}
	}
	void insert(T val) {
		sz++;
		arr.push_back(val);
		bubble_up(sz-1);
	}
	void pop() {
		std::swap(arr[sz-1], arr[0]);
		sz--;
		arr.pop_back();
		heapify(0);
	}
};

template<typename T, typename Container = std::vector<T>, typename Type_c = std::less<T> >
struct priority_queue : heap<T, Container, Type_c> {
	void push(T val) { this->insert(val); }
};

using namespace std;
#define MAXN 103

vector<pair<int, int> > adj[MAXN];
bool vis[MAXN];
int n;

void cleanup() {
	for(int i = 1; i <= n; i++) {
		adj[i].clear();  
		vis[i] = false;
	}
}

int dijk(int a, int b) {
	priority_queue<pair<int, int> > q;
	q.push(make_pair(0, a));
	while(!q.empty()) {
		pair<int, int> f = q.top();
		q.pop();
		if(f.second == b)	return f.first;
		if(vis[f.second])	continue;
		vis[f.second] = true;
		for(int i = 0; i < adj[f.second].size(); i++) {
			pair<int, int> c = adj[f.second][i];
			if(!vis[c.second]) {
				q.push(make_pair(f.first + c.first, c.second));  
			}
		}
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	int m, t, a, b, w;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n >> m;
		cleanup();
		while(m--) {
			cin >> a >> b >> w;
			adj[a].push_back(make_pair(w, b));
			adj[b].push_back(make_pair(w, a));
		}
		int res = dijk(1, n);
		cout << "Case " << tc << ": ";
		if(res == -1) {
			cout << "Impossible\n";  
		} else {
			cout << res << '\n';
		}
	}
	return 0;
}
