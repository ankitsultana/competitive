/* Author: Ankit Sultana
 * Problem id: 1291
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
 
class UnionFind{
    private:
        int V, Rank[MAXN], P[MAXN];
    public:
        UnionFind(int x)
        {
            V = x;
            REPc(i,0,x)
                Rank[i] = 1, P[i] = i;
        }
 
        int find_root(int x)
        {
            if(x == P[x])   return x;
            return P[x] = find_root(P[x]);
        }
 
        void Union(int x, int y)
        {
            int xr = find_root(P[x]), yr = find_root(P[y]);
            if(xr == yr)
                return ;
            if(Rank[xr] >= Rank[yr])
                Rank[xr] += Rank[yr], P[yr] = xr;
            else
                Rank[yr] += Rank[xr], P[xr] = yr;
        }
};
 
map<int, map<int, bool> > is_bridge;
int high[MAXN] = {0}, depth[MAXN] = {0}, n, ROOT;
bool vis[MAXN] = {false};
vector<pair<int, int> > bridges;
vi adj[MAXN];
void FindBridges(int node, int prev = -1)
{
    depth[node] = prev == -1?0: depth[prev]+1;
    vis[node] = true;
    high[node] = depth[node];
    int sz = int(SZ(adj[node])), child;
    REP(i,sz){
        child = adj[node][i];
        if(child == prev)   continue;
        if(vis[child]){
            high[node] = min(high[node], depth[child]);  
        }
        else{
            FindBridges(child, node);
            high[node] = min(high[node], high[child]);
            if(high[child] > depth[node]){
                bridges.PB(MP(node, child));
                is_bridge[node][child] = (is_bridge[child][node] = true);
            }
        }
    }
}
 
void initialise()
{
    bridges.clear();
    REPc(i,0,n){
        adj[i].clear();  
        high[i] = 0, depth[i] = 0, vis[i] = false;
    }
    is_bridge.clear();
    assert(int(is_bridge.size()) == 0);
}
 
int main()
{
    int t, E, a, b;
    scanf("%d", &t);
    REP1(tc,t){
        printf("Case %d: ", tc);  
        scanf("%d %d", &n, &E);
        initialise();
        while(E--){
            scanf("%d %d", &a, &b);
            adj[a].PB(b), adj[b].PB(a);
        }
        UnionFind UF(n);
        ROOT = 0;
        REP(i,n){
            if(vis[i])  continue;
            ROOT = i;
            FindBridges(i);
        }
        int CountKar[MAXN] = {0};
        REP(i,n){
            int sz = int(SZ(adj[i])), child, u, v;
            REP(j,sz){
                child = adj[i][j];
                if(!is_bridge[i][child]){
                    u = UF.find_root(i), v = UF.find_root(child);
                    UF.Union(u, v);
                }
            }
        }
        REP(i,int(SZ(bridges))){
            int u = bridges[i].F, v = bridges[i].S;
            u = UF.find_root(u), v = UF.find_root(v);
            CountKar[u]++, CountKar[v]++;
        }
        int answer = 0;
        REP(i,n){
            if(CountKar[i] == 1){
                answer++;
            }
        }
        printf("%d\n", (answer+1)/2);
    }
    return 0;
}
