/* Author: Ankit Sultana
 * Problem id: 1081
 * * * * * * * * * */
#include <stdio.h>
#include <cstring>
#include <limits>
#include <cmath>
#include <fstream>
#include <map>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <cassert>
#define LL long long
#define PB push_back
#define SWAP(a,b) a^=b,b^=a,a^=b
#define MP make_pair
#define vi vector<int>
#define vll vector<LL>
#define REP(i,n)	for(__typeof(n) i = 0; i < n; i++)
#define REP1(i,n)	for(__typeof(n) i = 1; i <= n; i++)
#define REPc(i,j,n)	for(__typeof(n) i = j; i <= n; i++)
#define FOR(i,c) for(__typeof(c.begin()) i = c.begin(); i != c.end(); i++)
#define F first
#define S second
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define mod 1000000007ll
#define SZ(a) int(a.size())
#define SZll(a) (LL)(a.size())
#define DECODE(x) int(x-'0')
#define ENCODE(x) char(x+'0')
#define what_is(x) cout<<#x<<" is "<<x<<'\n'
#define pii pair<int, int>
#define pll pair<LL, LL>
#define pil pair<int, LL>
#define pli pair<LL, int>

using namespace std;
#define MAXN 503
#define SIZE 5*MAXN

int n;
int segtrees[SIZE][SIZE];
int cor[SIZE][SIZE]; 
int node_cnt = 0, int_node_cnt = 0;
int Grid[MAXN][MAXN];

// merge segtrees[x], segtrees[y] and store in z
inline void merge_trees(int x, int y, int z) {
	REP(i,SIZE)	segtrees[z][i] = max(segtrees[x][i], segtrees[y][i]);
}
void reset_tree(const int &tree_no, const int &tree_co, int root = 1, int l = 1, int r = n) {
	int_node_cnt++;
	if(l == r) {
		segtrees[tree_no][root] = Grid[l][tree_co]; return ;
	}
	int mid = (l + r) >> 1;
	reset_tree(tree_no, tree_co, root*2, l, mid);
	reset_tree(tree_no, tree_co, root*2+1, mid+1, r);
	segtrees[tree_no][root] = max(segtrees[tree_no][root*2], segtrees[tree_no][root*2+1]);
}
void build_tree(int root = 1, int l = 1, int r = n) {
	assert(int_node_cnt < SIZE && node_cnt < SIZE);
	cor[l][r] = ++node_cnt, int_node_cnt = 0;
	if(l == r) {
		reset_tree(cor[l][r], l);	return ;
	}
	int mid = (l + r) >> 1;
	build_tree(root*2, l, mid);
	build_tree(root*2+1, mid+1, r);
	merge_trees(cor[l][mid], cor[mid+1][r], cor[l][r]);
}
int query_x(const int &tree_no, int &y1, int &y2, int root = 1, int l = 1, int r = n) {
	if(y1 > r || y2 < l)	return 0;
	if(l >= y1 && r <= y2)	return segtrees[tree_no][root];
	int mid = (l + r) >> 1, one, two;
	one = query_x(tree_no, y1, y2, root*2, l, mid);
	two = query_x(tree_no, y1, y2, root*2+1, mid+1, r);
	return max(one, two);  
}
// (x1, y1) top left corner
int query(int &x1, int &y1, int &x2, int &y2, int root = 1, int l = 1, int r = n) {
	if(x1 > r || x2 < l)	return 0;
	if(l >= x1 && r <= x2)	{
		// cout << "Entering for y in range: (" << y1 << ", " << y2 << ")\n";
		return query_x(cor[l][r], y1, y2);  
	}
	int mid = (l + r) >> 1, one, two;
	one = query(x1, y1, x2, y2, root*2, l, mid);
	two = query(x1, y1, x2, y2, root*2+1, mid+1, r);
	return max(one, two);
}

int main()
{
	int t, q, a1, b1, a2, b2, c;
	scanf("%d", &t);
	REP1(tc,t) {
		node_cnt = 0, int_node_cnt = 0;
		scanf("%d %d", &n, &q);
		REP1(i,n)	REP1(j,n)	scanf("%d", &Grid[i][j]);
		REP(i,SIZE)	fill(segtrees[i], segtrees[i] + SIZE, 0);
		build_tree();
		printf("Case %d:\n", tc);
		while(q--) {
			// cout << "---------------\n";
			scanf("%d %d %d", &a1, &b1, &c);
			a2 = a1 + c - 1, b2 = b1 + c - 1;
			assert(a2 != 0 && b2 != 0);
			printf("%d\n", query(b1, a1, b2, a2));
		}
	}
	return 0;
}
