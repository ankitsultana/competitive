/* Author: Ankit Sultana
 * Problem id: 1120
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
#define INF 1<<30
#define iNF std::numeric_limits<int>::max()
#define what_is(x) cout<<#x<<" is "<<x<<'\n'
#define pii pair<int, int>
#define pll pair<LL, LL>
#define pil pair<int, LL>
#define pli pair<LL, int>

using namespace std;

template<typename T> T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }
template<typename T> T LCM(T a, T b) { return a*(b/gcd(a, b)); }
template<typename T> T expo(T b, T e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }
template<class T, class S> std::ostream& operator<<(std::ostream &os, const std::pair<T, S> &t) {
	os<<"("<<t.first<<", "<<t.second<<")";  
	return os;
}
template<class T> std::ostream& operator<<(std::ostream &os, const std::vector<T> &t) {
	os<<"["; FOR(it,t) { if(it != t.begin()) os<<", "; os<<*it; } os<<"]";
	return os;
}
namespace variadic {
	template<typename T> T min(T v) { return v; }
	template<typename T, typename... Args> T min(T f, Args... args) {
		return std::min(f, min(args...)); }
	template<typename T> T max(T v) { return v; }
	template<typename T, typename... Args> T max(T f, Args... args) { 
		return std::max(f, max(args...)); }
}
#define MAXN 30010
#define gc getchar_unlocked
template <typename T> void scanint(T &x) {
	T c = gc();
	while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0;
	for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

int n, tree_size;
struct segnode {
	LL length;
	int l, r, open;
} segtree[MAXN*50];

struct event {
	LL t, y1, y2, type;
	bool operator<(const event &other) const {
		return t == other.t?type > other.type: t < other.t;
	}
}events[MAXN*2];

void segupdate(int &x, int l, int r, int ql, int qr, int type)
{
	if(qr < ql)	swap(ql, qr);
	if(!x) {
		x = ++tree_size;
		segtree[x] = {0, 0, 0, 0};
	}
	if(l >= ql && r <= qr) {
		segtree[x].open += type;
		if(segtree[x].open == 0) {
			segtree[x].length = segtree[segtree[x].l].length + segtree[segtree[x].r].length;  
		}
		else if(segtree[x].open == 1) {
			segtree[x].length = (LL)r - l + 1;  
		}
		return ;
	}
	int mid = (r - l)/2 + l;
	if(mid >= ql) {
		segupdate(segtree[x].l, l, mid, ql, qr, type);
	}
	if(qr > mid) {
		segupdate(segtree[x].r, mid+1, r, ql, qr, type);  
	}
	if(segtree[x].open == 0) {
		segtree[x].length = segtree[segtree[x].l].length + segtree[segtree[x].r].length;  
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	REP1(tc,t) {
		tree_size = 0;
		int x1, x2, y1, y2;
		scanf("%d", &n);
		int max_y = 0;
		REP(i,n) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			events[i*2] = {x1, y1, y2, 1};
			events[i*2+1] = {x2, y1, y2, -1};
			max_y = variadic::max(max_y, y1, y2);
		}
		sort(events, events + 2*n);
		int transfer = 0;
		LL prev = events[0].t, res = 0, temp;
		REP(i,2*n) {
			temp = (LL)(segtree[transfer].length - 1) * (events[i].t - prev);
			res += temp;
			segupdate(transfer, 0, max_y, events[i].y1, events[i].y2, events[i].type);
			prev = events[i].t;
		}
		printf("Case %d: %lld\n", tc, res);
		// printf("%lld\n", res);
	}
	return 0;
}
