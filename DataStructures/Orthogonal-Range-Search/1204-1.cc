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
#define INF 1<<30
#define SIZE 6*MAXN

int n, k;
map<int, int> compress;
int rake[3*MAXN];

struct event {
	int t, a, b, open;
	bool operator<(const event &other) const {
		return t == other.t?open > other.open: t < other.t;
	}
}events[2*MAXN];

int counter[SIZE], sum[SIZE], down[SIZE];
void update(int root, int l, int r, int ql, int qr, int type, int propagate) {
	int mid = (l + r) >> 1, c = root * 2;
	if(l >= ql && r <= qr) {
		// cout << "HERE: " << l << ", " << r << endl;
		counter[root] += type;
		if(counter[root] + propagate >= k)	sum[root] = rake[r] - rake[l];
		else {
			if(l + 1 >= r) {
				sum[root] = 0;
				return ;
			}
			update(c, l, mid, ql, qr, 0, propagate + counter[root]);
			update(c + 1, mid, r, ql, qr, 0, propagate + counter[root]);
			sum[root] = sum[c] + sum[c + 1];
		}
		return ; 
	}
	if(l + 1 >= r) {
		if(counter[root] + propagate >= k)
			sum[root] = rake[r] - rake[l];
		else
			sum[root] = 0;
		return ;
	}
	if(ql < mid)
		update(c, l, mid, ql, qr, type, propagate + counter[root]);
	if(qr > mid)
		update(c+1, mid, r, ql, qr, type, propagate + counter[root]);
	if(propagate + counter[root] >= k)
		sum[root] = rake[r] - rake[l];
	else
		sum[root] = sum[c] + sum[c + 1];
}

int main()
{
	int t, a, b, c, d;
	scanf("%d", &t);
	REP1(tc,t) {
		compress.clear();
		fill(counter, counter + SIZE, 0);
		fill(sum, sum + SIZE, 0);
		scanf("%d %d", &n, &k);
		REP(i,n) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			if(a > c)swap(a, c);if(b > d)swap(b, d);
			d++, c++;
			compress[b] = 0, compress[d] = 0;
			events[i*2] = {a, b, d, 1};
			events[i*2+1] = {c, b, d, -1};
		}
		int cnt = 0;
		FOR(it,compress) {
			it->S = ++cnt;
			rake[cnt] = it->F;
		}
		sort(events, events + 2*n);
		LL res = 0, prev = events[0].t, temp;
		REP(i,2*n) {
			temp = (LL)(sum[1]) * (events[i].t - prev);
			res += temp;
			update(1, 1, cnt, compress[events[i].a], compress[events[i].b], events[i].open, 0);
			prev = events[i].t;
		}
		printf("Case %d: %lld\n", tc, res);
	}
	return 0;
}
