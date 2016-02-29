/* Author: Ankit Sultana
 * Problem id: 1278
 * * * * * * * * * */
#ifdef __APPLE__
	#include <iostream>
#endif
#include <stdio.h>
#include <cassert>
#include <vector>
#define MAXN 9999991ull
#define sq(x) ((x)*(x))
#define mset(x,v) memset(x,v,sizeof(x))
#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))
#define LEN 664578
#define LL long long

using namespace std;
unsigned LL base[MAXN/64]; 
LL primes[LEN];
void sieve() {
	unsigned LL i, j, k;
	for(i=3; i<LEN; i+=2) if(!chkC(base, i))
		for(j=i*i, k=i<<1; j<MAXN; j+=k)
			setC(base, j);
	primes[0] = 2;
	for(i=3, j=1; i<MAXN; i+=2) if(!chkC(base, i))
		primes[j++] = i;
}
LL count_divisors(LL n) {
	LL ans = 1, iter, cnt;
	for(iter = 1; iter < LEN && primes[iter] * primes[iter] <= n; iter++) {
		cnt = 0;
		while(n % primes[iter] == 0) {
			cnt++;
			n /= primes[iter];
		}
		ans *= cnt + 1;
	}
	if(n > 1 && n % 2 == 1)
		ans = ans * 2ll;
	return ans;
}

int main() {
	int t;
	sieve();
	LL n;
	scanf("%d", &t);
	for(int tc = 1; tc <= t; tc++) {
		scanf("%lld", &n);
		while(n % 2 == 0)	n /= 2;
		LL res = count_divisors(n);
		res--;
		printf("Case %d: %lld\n", tc, res);
	}
	return 0;
}
