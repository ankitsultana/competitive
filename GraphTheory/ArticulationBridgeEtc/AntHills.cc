/* Author: Ankit Sultana
 * Problem id: 1063
 * * * * * * * * * */
#include <stdio.h>
#include <map>
#include <algorithm>
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
#define F first
#define S second
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define mod 1000000007ll
#define SZ(a) int(a.size())
#define SZll(a) (LL)(a.size())
#define MAXN 10003
 
using namespace std;
 
template<typename T> T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }
template<typename T> T LCM(T a, T b) { return a*(b/gcd(a, b)); }
template<typename T> T expo(T b, T e, const T &m){if(e <= 1)return e == 0?1: b;\
    return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2); }
 
int high[MAXN] = {0}, depth[MAXN] = {0}, n;
bool vis[MAXN] = {false};
bool is_articulate[MAXN] = {false};
vector<int> result;
vi adj[MAXN];
int ROOT;
void FindArticulate(int node, int prev = -1)
{
    depth[node] = prev == -1?0: depth[prev]+1;
    vis[node] = true;
    high[node] = depth[node];
    int sz = SZ(adj[node]), child;
    int children = 0;
    REP(i,sz){
        child = adj[node][i];
        if(child == prev)   continue;
        if(vis[child]){
            high[node] = min(high[node], depth[child]);  
        }
        else{
            children++;
            FindArticulate(child, node);
            high[node] = min(high[node], high[child]);
            if(node == ROOT && children > 1){
                is_articulate[node] = true;  
            }
            if(node != ROOT && high[child] >= depth[node]){
                is_articulate[node] = true;
            }
        }
    }
}
 
int main()
{
    int t;
    scanf("%d", &t);
    REP1(tc,t){
        int E;
        printf("Case %d: ", tc);
        scanf("%d %d", &n, &E);
        result.clear();
        REP1(i,n){
            depth[i] = high[i] = 0;  
            vis[i] = false;
            is_articulate[i] = false;
            adj[i].clear();
        }
        int a, b;
        while(E--){
            scanf("%d %d", &a, &b);
            adj[a].PB(b), adj[b].PB(a);
        }
        REP1(i,n){
            if(vis[i])  continue;
            ROOT = i;
            FindArticulate(i);
        }
        int answer = 0;
        REP1(i,n){
            if(is_articulate[i])
                answer++;
        }
        printf("%d\n", answer);
    }
    return 0;
}
