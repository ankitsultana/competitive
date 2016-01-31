/* Author: Ankit Sultana
 * Problem id: 1161
 * * * * * * * * * */
#include <iostream>
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
#define MAXD 6

bool is_prime[MAXN];
vi primes;
int n, arr[MAXN];
void sieve() {
	fill(is_prime, is_prime + MAXN, true);
	is_prime[1] = false;
	for(int i = 2; i*i < MAXN; i++) {
		if(is_prime[i]) {
			for(int j = i*i; j < MAXN; j += i) {
				is_prime[j] = false;
			}
		}
	}
	REPc(i,2,MAXN-1)
		if(is_prime[i])
			primes.PB(i);
}

int lp[MAXN];
void precomp_lowest_primes()
{
	lp[1] = -1;
	for(int i = 2; i < MAXN; i++){
		if(lp[i] == 0)
			lp[i] = -1, primes.push_back(i);
		int z = lp[i];
		if(lp[i] == -1) z = i;
		for(int j = 0; j < primes.size() && primes[j] <= z && i*primes[j] < MAXN; j++){
			lp[i*primes[j]] = primes[j];
		}
	}
	REP(i,MAXN){
		if(lp[i] <= 0){
			lp[i] = i;  
		}
	}
}
LL c[MAXN];
vector<pii> sq_free;

LL nCr(LL n) {
	return n * (n-1) * (n-2) * (n-3) / (2 * 3 * 4);
}

int main()
{
	ios_base::sync_with_stdio(false);
	sieve();
	precomp_lowest_primes();
	// find square free numbers and the number of their prime divisors
	REPc(i,2,MAXN-1) {
		int temp = i, cnt = 0;
		bool check = true;
		REP(j,SZ(primes)) {
			if(primes[j] > temp)	break;
			if(temp % primes[j] == 0) {
				temp /= primes[j];
				if(temp % primes[j] == 0) {
					check = false;
					break;
				} else {
					cnt++;  
				}
			}
		}
		if(check && i < 10001)
			sq_free.PB(MP(i, cnt));
	}
	//  Done
	int t;
	cin >> t;
	REP1(tc,t) {
		fill(c, c + MAXN, 0);
		LL ans = 0;
		cin >> n;
		REP1(i,n) {
			cin >> arr[i];
			vi temp_v;
			// cout << "DEBUG: " << arr[i] << " == ";
			while(arr[i] > 1) {
				int temp = lp[arr[i]];
				temp_v.PB(temp);
				while(arr[i] % temp == 0) {
					arr[i] /= temp;
				}
			}
			int size = temp_v.size();
			REP(j,1<<size) {
				if(j == 0)	continue;
				int temp = 1;
				REP(k,size) {
					if((1<<k)&j) {
						temp = temp * temp_v[k];
					}
					if(temp > MAXN)	break;
				}
				if(temp < MAXN) {
					// cout << "SHIT: " << temp << endl;
					c[temp]++;
				}
			}
			// cout << temp_v << endl;
		}	
		// cout << "DEBUG: " << c[2] << endl;
		REP(j,SZ(sq_free)) {
			pii elem = sq_free[j];
			if(elem.S % 2 == 0) {
				ans -= nCr(c[elem.F]);
			} else {
				ans += nCr(c[elem.F]);
			}
		}
		ans = nCr((LL)n) - ans;
		cout << "Case " << tc << ": " << ans << '\n';
	}
	return 0;
}
