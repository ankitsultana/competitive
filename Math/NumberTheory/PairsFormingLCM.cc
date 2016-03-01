/* Author: Ankit Sultana
 * Problem id: 1236
 * * * * * * * * * */
#include <iostream>
#define LL long long
#define MAXN 99999989ull 
#define sq(x) ((x)*(x))
#define mset(x,v) memset(x,v,sizeof(x))
#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))
#define LEN 5761455

using namespace std;
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
	ios_base::sync_with_stdio(false);
	sieve();
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		LL n;
		cin >> n;
		LL res = 1;
		int iter = 0;
		for(iter = 0; (LL)primes[iter] * primes[iter] <= n; iter++) {
			LL cnt = 0;
			while(n % primes[iter] == 0) {
				n /= primes[iter];
				cnt++;
			}
			res *= 2*cnt + 1;
		}
		if(n > 1)	res *= 3;
		res++;
		res /= 2;
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
