/* Author: Ankit Sultana
 * Problem id: 1259
 * * * * * * * * * */
#ifdef __APPLE__
	#include <iostream>
#endif
#include <stdio.h>
#include <algorithm>
#include <vector>
#define gc getchar_unlocked
#define MAXN 9999999ull 
#define sq(x) ((x)*(x))
#define mset(x,v) memset(x,v,sizeof(x))
#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))
#define LEN 664579
#define LL long long

using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x; }
bool is_com[MAXN];
unsigned int base[MAXN/64]; 
int primes[LEN];
void sieve() {
	unsigned LL i, j, k;
	for(i=3; i<LEN; i+=2) if(!chkC(base, i))
		for(j=i*i, k=i<<1; j<MAXN; j+=k)
			setC(base, j);
	primes[0] = 2;
	for(i=3, j=1; i<MAXN; i+=2) if(!chkC(base, i))
		primes[j++] = i;
}
int main() {
	LL n, res;
	sieve();
	int t;
	scanint(t);
	for(int tc = 1; tc <= t; tc++) {
		scanint(n);
		int lower = 0, upper, res = 0;
		upper = (int)(lower_bound(primes, primes + LEN, n - 2) - primes);
		if(upper == LEN)	upper--;
		while(lower <= upper) {
			if(primes[lower] + primes[upper] == n) {
				res++;
				lower++, upper--;
			} else if(primes[lower] + primes[upper] > n) {
				upper--;
			} else {
				lower++;  
			}
		}
		printf("Case %d: %d\n", tc, res);
	}
	return 0;
}
