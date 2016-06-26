/* Author: Ankit Sultana
 * Problem id: 1215
 * * * * * * * * * */
#ifdef __APPLE__
	#include <iostream>
#endif
#include <stdio.h>
#include <algorithm>
#define LL long long
#define INF 1ll<<61

using namespace std;
template<typename T> T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }
template<typename T> T LCM(T a, T b) { return a*(b/gcd(a, b)); }

int main() {
	int t;
	scanf("%d", &t);
	for(int tc = 1; tc <= t; tc++) {
		printf("Case %d: ", tc);
		LL a, b, L, l;
		scanf("%lld %lld %lld", &a, &b, &L);
		l = LCM(a, b);
		LL iter = 1, res = INF;
		while(iter*iter <= L) {
			if(L % iter == 0) {
				if(LCM(l, iter) == L)
					res = min(res, iter);
			}
			if(L % (L/iter) == 0) {
				if(LCM(l, L/iter) == L)
					res = min(res, L/iter);
			}
			iter++;
		}
		if(res != INF) {
			printf("%lld\n", res);
		} else {
			printf("impossible\n");
		}
	}
	return 0;
}
