/* Author: Ankit Sultana
 * Problem id: 1204
 * * * * * * * * * */
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
#define MAXN 30003
#define INF (int)1e9+9
#define SIZE 50*MAXN

int n, k;

struct event {
	int t, a, b, open;
	bool operator<(const event &other) const {
		return t == other.t?open > other.open: t < other.t;
	}
}events[2*MAXN];

struct node {
	int sum, counter, l, r;
}tree[SIZE];
int tree_size = 0;
#include <iostream>
void update(int &x, int l, int r, int ql, int qr, int type, int propagate) {
	if(!x) {
		x = ++tree_size;
		tree[x] = {0, 0, 0, 0};
	}
	cout << l << ' ' << r << ' '<< tree_size << endl;
	int mid = (r - l)/2 + l;
	if(l >= ql && r <= qr) {
		tree[x].counter += type;
		if(propagate + tree[x].counter >= k)	tree[x].sum = r - l;
		else {
			if(l + 1 >= r) {
				tree[x].sum = 0;
				return ;
			}
			update(tree[x].l, l, mid, ql, qr, 0, propagate + tree[x].counter);
			update(tree[x].r, mid, r, ql, qr, 0, propagate + tree[x].counter);
			tree[x].sum = tree[tree[x].l].sum + tree[tree[x].r].sum;
		}
		return ;
	}
	if(l + 1 >= r) {
		if(propagate + tree[x].counter >= k)
			tree[x].sum = r - l;
		else
			tree[x].sum = 0;
		return ;
	}
	if(ql < mid)
		update(tree[x].l, l, mid, ql, qr, type, propagate + tree[x].counter);
	if(qr > mid)
		update(tree[x].r, mid, r, ql, qr, type, propagate + tree[x].counter);
	if(propagate + tree[x].counter >= k)
		tree[x].sum = r - l;
	else
		tree[x].sum = tree[tree[x].l].sum + tree[tree[x].r].sum;
}

int main()
{
	int t, a, b, c, d;
	scanf("%d", &t);
	tree[0] = {0, 0, 0, 0};
	REP1(tc,t) {
		tree_size = 0;
		scanf("%d %d", &n, &k);
		REP(i,n) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			if(a > c)swap(a, c);if(b > d)swap(b, d);
			d++, c++;
			events[i*2] = {a, b, d, 1};
			events[i*2+1] = {c, b, d, -1};
		}
		sort(events, events + 2*n);
		LL res = 0, prev = events[0].t, temp;
		int tr = 0;
		REP(i,2*n) {
			temp = (LL)(tree[tr].sum) * (events[i].t - prev);
			res += temp;
			update(tr, 0, INF, events[i].a, events[i].b, events[i].open, 0);
			prev = events[i].t;
		}
		printf("Case %d: %lld\n", tc, res);
	}
	return 0;
}
