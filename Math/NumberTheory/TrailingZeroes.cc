/* Author: Ankit Sultana
 * Problem id: 1090
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
#define MAXN 10003

bool is_prime[MAXN] = {false};
vll primes;
void sieve_eratosthenes()
{
	REP(i,MAXN)	is_prime[i] = true;
	is_prime[1] = false;
	for(int i = 2; i*i <= MAXN; i++){
		if(is_prime[i]){
			for(int j = i*i; j < MAXN; j += i){
				is_prime[j] = false;
			}
		}
	}
	REPc(i,2,MAXN-1){
		if(is_prime[i])
			primes.PB(i);  
	}
}

/* Miller Rabbin,
 * Complexity: O(k * log2^3(n))
 * * * * * * * * * * * */
inline LL multiply(LL a, LL b, const LL &m)
{
	a %= m, b %= m; 
	long double res = a;res *= b;
	LL c = (LL)(res/m); 
	a *= b, a -= c*m, a %= m;
	if(a < 0)	
		a += m; 
	return a;
}

inline LL power(LL a, LL b, const LL &m)
{
	LL ans = 1;  
	while(b) {
		if(b & 1) {
			ans = multiply(ans, a, m);
		}
		a = multiply(a, a, m);
		b >>= 1;
	}
	return ans;
}

// Returns true if p is prime
inline bool Miller(LL p) {
	int b[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
	if(p < 2)	return false;  
	if(p != 2 && !(p&1))	return false;
	for(int i = 0; i < 25; i++) {
		if(p == b[i])	return true;  
		else if(p % b[i] == 0)	return false;
	}
	int cnt = 0;
	LL s = p-1;
	while(!(s&1)) {
		s /= 2;  
		cnt++;
	}
	LL accuracy = 2, m;
	for(int i = 0; i < accuracy; i++) {
		LL a = rand() % (p-1) + 1;
		m = p;
		LL x = power(a, s, m);
		if(x == 1 || x == p-1)	continue;
		int flag = 0;
		for(int i = 1; i < cnt; i++) {
			x = multiply(x, x, m);  
			if(x == 1)	return false;
			if(x == p-1) {
				flag = 1;  
				break;
			}
		}
		if(flag)	continue;
		return false;
	}
	return true;
}

LL count_divisors(LL n)
{
	LL ans = 1;
	REP(j,SZ(primes)) {
		LL p = primes[j];
		if(p*p*p > n)	break;
		LL count = 1;
		while(n % p == 0) {
			n /= p;
			count++;
		}
		ans = ans*count;
	}
	LL sq = sqrt(double(n));
	if(Miller(n)) {
		ans = ans*2;
	}
	else if(sq*sq == n && Miller(sq)) {
		ans *= 3;
	}
	else if(n != 1) {
		ans *= 4;
	}
	return ans;
}

int main()
{
	sieve_eratosthenes();
	int t;
	scanf("%d", &t);
	REP1(tc,t) {
		LL n;
		scanf("%lld", &n);
		LL res = count_divisors(n);
		printf("Case %d: %lld\n", tc, res - 1);
	}
	return 0;
}
