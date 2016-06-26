/* Author: Ankit Sultana
 * Problem id: 1046
 * * * * * * * * * */
#include <iostream>
#include <vector>
#include <queue>
#define PB push_back
#define MAXN 11
#define INF 1<<28

using namespace std;
vector<int> dr;// = {1,1,2,2,-1,-1,-2,-2};
vector<int> dc;// = {2,-2,1,-1,2,-2,1,-1};
int val[MAXN][MAXN], cache[MAXN][MAXN], no_rows, no_cols, depth[MAXN][MAXN];
bool vis[MAXN][MAXN];
string Grid[MAXN];

void cleanup() {
	for(int i = 0; i < no_rows; i++)
		for(int j = 0; j < no_cols; j++)
			val[i][j] = 0;
}

inline bool valid(int r, int c) {
	return r >= 0 && r < no_rows && c >= 0 && c < no_cols;  
}

void BFS(int k, int r, int c) {
	queue<pair<int, int> > q;
	q.push(make_pair(r, c));
	while(!q.empty()) {
		pair<int, int> f = q.front();
		q.pop();
		if(vis[f.first][f.second])	continue;
		vis[f.first][f.second] = true;
		for(int i = 0; i < dr.size(); i++) {
			int alt_r = dr[i] + f.first, alt_c = dc[i] + f.second;
			if(valid(alt_r, alt_c) && !vis[alt_r][alt_c]) {
				depth[alt_r][alt_c] = min(depth[alt_r][alt_c], depth[f.first][f.second] + 1);
				cache[alt_r][alt_c] = min(cache[alt_r][alt_c], (depth[alt_r][alt_c] - 1) / k + 1);
				q.push(make_pair(alt_r, alt_c));
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	dr.PB(1), dr.PB(1), dr.PB(2), dr.PB(2), dr.PB(-1), dr.PB(-1), dr.PB(-2), dr.PB(-2);
	dc.PB(2), dc.PB(-2), dc.PB(1), dc.PB(-1), dc.PB(2), dc.PB(-2), dc.PB(1), dc.PB(-1);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> no_rows >> no_cols;
		cleanup();
		bool check = true;
		for(int i = 0; i < no_rows; i++) {
			cin >> Grid[i];
		}
		for(int i = 0; i < no_rows; i++) {
			for(int j = 0; j < no_cols; j++) {
				if(Grid[i][j] != '.') {
					check = false;
					for(int i = 0; i < no_rows; i++)	
						for(int j = 0; j < no_cols; j++)	
							vis[i][j] = false, cache[i][j] = INF, depth[i][j] = INF;
					cache[i][j] = 0, depth[i][j] = 0;
					BFS(Grid[i][j] - '0', i, j);
					for(int i = 0; i < no_rows; i++) {
						for(int j = 0; j < no_cols; j++) {
							if(cache[i][j] == INF || val[i][j] == INF) {
								val[i][j] = INF;  
							} else {
								val[i][j] += cache[i][j];
							}
						}
					}
				}
			}
		}
		int res = INF;
		if(!check) {
			for(int i = 0; i < no_rows; i++)
				for(int j = 0; j < no_cols; j++)
					res = min(res, val[i][j]);
			if(res == INF)
				res = -1;
		} else {
			res = 0;  
		}
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
