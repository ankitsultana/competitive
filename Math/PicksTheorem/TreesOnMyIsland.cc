/*  Author: Ankit Sultana
 * * * * * * * * * * * * * * * * */
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
#define REP(i,n)    for(__typeof(n) i = 0; i < n; i++)
#define REP1(i,n)   for(__typeof(n) i = 1; i <= n; i++)
#define REPc(i,j,n) for(__typeof(n) i = j; i <= n; i++)
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
#define INF std::numeric_limits<LL>::max()
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
#define MAXN 10003
LL res = 0, n, x[MAXN], y[MAXN], b, A;
 
int main()
{
    int t;
    scanf("%d", &t);
    REP1(tc,t) {
        printf("Case %d: ", tc);
        // i + b/2 - 1 = A
        // A is calculable, b is calculable
        res = 0, b = 0, A = 0;
        scanf("%lld", &n);
        REP1(i,n) {
            scanf("%lld %lld", &x[i], &y[i]);
        }
        REP1(i,n) {
            if(i == 1) {
                b += gcd(abs(x[1] - x[n]), abs(y[1] - y[n])) + 1;
                continue;
            }
            b += gcd(abs(x[i] - x[i-1]), abs(y[i] - y[i-1])) + 1;
        }
        b -= n;
        REP1(i,n) {
            if(i == 1) {
                A += x[1]*y[n] - x[n]*y[1];
                continue;
            }
            A += x[i]*y[i-1] - y[i]*x[i-1];
        }
        // i = A - b/2 + 1
        // i = (2*A - b)/2 + 1
        A = abs(A);
        res = (A - b)/2;
        res++;
        printf("%lld\n", res);
    }
    return 0;
}
