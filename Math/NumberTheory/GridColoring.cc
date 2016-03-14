/* Author: Ankit Sultana
 * Problem id: 1333
 * * * * * * * * * */
#include <iostream>
#include <map>
#include <vector>
#define S second
#define F first
#define LL long long
#define mod 1000000000ll

using namespace std;
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}

inline LL go(LL k, LL n) {
	return n <= 0?1: (k * expo(k-1, n-1, mod)) % mod;
}

template<typename T>
inline T next_iter(T x) {
	return ++x;
}
template<typename T>
inline T prev_iter(T x) {
	return --x;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		LL res, no_rows, no_cols, k, b;
		int r, c;
		cin >> no_rows >> no_cols >> k >> b;
		map<LL, map<LL, bool> > cols;
		res = 1;
		for(int i = 0; i < b; i++) {
			cin >> r >> c;
			cols[c][r] = true;
			cols[c][no_rows+1] = true;
			cols[c][0] = true;
		}
		int infected = cols.size();
		for(map<LL, map<LL, bool> >::iterator it = cols.begin(); it != cols.end(); it++) {
			// it->S returns the map for that column
			map<LL, bool> temp = it->S;
			for(map<LL, bool>::iterator jt = next_iter(temp.begin()); jt != temp.end(); jt++) {
				res *= go(k, jt->F - prev_iter(jt)->F - 1);
				res %= mod;
			}
		}
		res *= expo(go(k, no_rows), no_cols - infected, mod);
		res %= mod;
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
