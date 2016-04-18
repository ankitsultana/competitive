/* Author: Ankit Sultana
 * Problem Name: Distributing Chocolates (1325)
 * * * * * * * * * */
#include <iostream>
#include <cstring>
#include <limits>
#include <cmath>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
#define LL long long
#define PB push_back
#define MP make_pair
#define vi vector<int>
#define REP(i,n)    for(__typeof(n) i = 0; i < n; i++)
#define REP1(i,n)   for(__typeof(n) i = 1; i <= n; i++)
#define REPc(i,j,n) for(__typeof(n) i = j; i <= n; i++)
#define F first
#define S second
#define mod 100000007ll
#define INF std::numeric_limits<LL>::max()
#define iNF std::numeric_limits<int>::max()
using namespace std;
/* Returns smallest number such
 * that, a^x === b mod m
 * * * * * * * * * * * * * * * */
template<typename T>
T baby_step (T a, T b, T m) {
    T n = (T) sqrt (m + .0) + 1;
 
    T an = 1;
    for (T i=0; i<n; ++i)
        an = (an * a) % m;
 
    map<T,T> vals;
    for (T i=1, cur=an; i<=n; ++i) {
        if (!vals.count(cur))
            vals[cur] = i;
        cur = (cur * an) % m;
    }
 
    T final_ans = INF;
    for (T i=0, cur=b; i<=n; ++i) {
        if (vals.count(cur)) {
            T ans = vals[cur] * n - i;
            if (ans < m && ans != 0) {
                final_ans = min(final_ans, ans);  
            }
        }
        cur = (cur * a) % m;
    }
    return final_ans == INF?-1: final_ans;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    int t;
    cin>>t;
    REP1(tc,t) {
        LL k, result;
        cin>>k>>result;
        LL ans = baby_step(k, result, mod);
        cout<<"Case "<<tc<<": "<<ans<<'\n';
    }
    return 0;
}
