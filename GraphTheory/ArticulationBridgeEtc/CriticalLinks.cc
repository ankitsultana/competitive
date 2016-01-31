/* Author: Ankit Sultana
 * Problem id: 1026
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
 
int n, t;
 
int high[MAXN] = {0}, depth[MAXN] = {0};
bool vis[MAXN] = {false};
 
vector<pair<int, int> > result;
vi adj[MAXN];
 
void FindBridges(int node, int prev = -1)
{
    depth[node] = prev == -1?0: depth[prev]+1;
    vis[node] = true;
    high[node] = depth[node];
    int sz = SZ(adj[node]), child;
    REP(i,sz){
        child = adj[node][i];
        if(child == prev)   continue;
        if(vis[child]){
            high[node] = min(high[node], depth[child]);  
        }
        else{
            FindBridges(child, node);
            high[node] = min(high[node], high[child]);
            //cout<<"DEBUG: "<<node<<' '<<child<<endl;
            //cout<<"VALUE: "<<high[child]<<' '<<depth[node]<<endl;
            if(high[child] > depth[node]){
                result.PB(MP(node, child));
            }
        }
    }
}
 
struct myCompare{
    bool operator()(const pair<int, int> &lhs, const pair<int, int> &rhs)
    {
        if(lhs.F == rhs.F)
            return lhs.S < rhs.S;
        return lhs.F < rhs.F;
    }
};
 
int main()
{
    scanf("%d", &t);
    REP1(tc,t){
        result.clear();
        scanf("%d", &n);
        REP(i,n){
            depth[i] = (high[i] = 0);  
            vis[i] = false;
            adj[i].clear();
        }
        printf("Case %d:\n", tc);
        int curr_node, num, tmp;
        REP(i,n){
            scanf("%d", &curr_node);  
            scanf(" (%d)", &num);
            while(num--){
                scanf("%d", &tmp);
                adj[tmp].PB(curr_node), adj[curr_node].PB(tmp);
            }
        }
        REP(i,n){
            if(vis[i])  continue;
            FindBridges(i);
        }
        int sz = int(SZ(result));
        printf("%d critical links\n", sz);
        REP(i,sz){
            if(result[i].F > result[i].S)
                SWAP(result[i].F,result[i].S);
        }
        sort(result.begin(), result.end(), myCompare());
        REP(i,sz){
            printf("%d - %d\n", result[i].F, result[i].S);
        }
    }
    return 0;
}
