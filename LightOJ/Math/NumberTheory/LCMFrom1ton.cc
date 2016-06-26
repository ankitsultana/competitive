/* Author: Ankit Sultana
 * Problem id: 1289
 * Comment: Bitwise Sieve
 * * * * * * * * * */
#ifdef __APPLE__
	#include <iostream>
#endif
#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>
#define LL long long
#define gc getchar_unlocked

#define MAXN 99999999u 
#define ROOTN 10003
#define mod 4294967296u
#define sq(x) ((x)*(x))
#define mset(x,v) memset(x,v,sizeof(x))
#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))
#define SIZE 5761455
using namespace std;

unsigned int base[MAXN/64], primes[SIZE], prefix[SIZE];

void sieve() {
	unsigned LL i, j, k;
	for(i=3; i<SIZE; i+=2) if(!chkC(base, i))
		for(j=i*i, k=i<<1; j<MAXN; j+=k)
			setC(base, j);
	primes[0] = 2;
	for(i=3, j=0; i<MAXN; i+=2) if(!chkC(base, i))
		primes[++j] = i;
}

void precompute() {
	sieve();
	prefix[0] = 2;
	for(int i = 1; i < SIZE; i++)
		prefix[i] = prefix[i-1] * primes[i];
}

int main() {
	precompute();
	int t; 
	unsigned int n;
	scanf("%d", &t);
	for(int tc = 1; tc <= t; tc++) {
		unsigned int answer = 1;
		scanf("%u", &n);
		int idx = int(upper_bound(primes, primes + SIZE, n) - primes) - 1;
		answer = prefix[idx];
		// Now for powers > 1
		int rootn = (int)(sqrt((float)n));
		for(int i = 0; primes[i] <= rootn; i++) {
			unsigned int temp = primes[i];
			// Check overflow
			while(temp < mod/primes[i] && temp*primes[i] <= n) {
				temp = temp*primes[i];
			}
			temp /= primes[i];
			answer = answer*temp;
		}
		printf("Case %d: %u\n", tc, answer);
	}
	return 0;
}
