/* Author: Ankit Sultana
 * Problem id: 1300
 * * * * * * * * * */
#include <iostream>
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
#define INF 1<<28
#define MAXN 20003
 
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
 
 
int high[MAXN] = {0}, depth[MAXN] = {0}, n, ROOT;
bool vis[MAXN] = {false};
vector<pair<int, int> > adj[MAXN];
bool is_bridge[MAXN] = {false};
bool color[MAXN] = {false};
int comp[MAXN] = {0}, temp[MAXN] = {0};
int comp_sizes[MAXN] = {0};
void FindBridges(int node, int prev = -1)
{
    depth[node] = prev == -1?0: depth[prev]+1;
    vis[node] = true;
    high[node] = depth[node];
    int sz = SZ(adj[node]), child;
    REP(i,sz){
        child = adj[node][i].F;
        if(child == prev)   continue;
        if(vis[child]){
            high[node] = min(high[node], depth[child]);  
        }
        else{
            FindBridges(child, node);
            high[node] = min(high[node], high[child]);
            if(high[child] > depth[node]){
                // result.PB(MP(node, child));
                is_bridge[adj[node][i].S] = true;
            }
        }
    }
}
 
int m;
int num_comp = 0;
void compress_bridge_comp(int node, int comp_no, bool vis[])
{
    if(vis[node])   return ;
    vis[node] = true;
    int sz = int(adj[node].size());
    comp[node] = comp_no;
    comp_sizes[comp_no]++;
    REP(i,sz){
        if(vis[adj[node][i].F]) continue;
        compress_bridge_comp(adj[node][i].F, is_bridge[adj[node][i].S]?++num_comp: comp_no, vis);
    }
}
 
void initialise()
{
    cin>>n>>m;
    REPc(i,0,n){
        adj[i].clear();  
        high[i] = 0, depth[i] = 0, vis[i] = false;
        comp_sizes[i] = 0;
    }
    num_comp = 0;
    REPc(i,0,m){
        is_bridge[i] = false;  
    }
    int a, b;
    REP(i,m){
        cin>>a>>b;  
        a++, b++;
        adj[a].PB(MP(b, i+1)), adj[b].PB(MP(a, i+1));
    }
}
 
void solve()
{
    REP1(i,n){
        if(vis[i])  continue;
        ROOT = i;
        FindBridges(ROOT, -1);
    }
}
 
bool colorable(int node, int comp_no, bool vis[])
{
    int sz = int(adj[node].size());
    vis[node] = true;
    REP(i,sz){
        if(vis[adj[node][i].F] && color[adj[node][i].F] == color[node] &&
                comp_no == comp[adj[node][i].F]){
            return false;
        }
    }
    REP(i,sz){
        if(vis[adj[node][i].F] || comp[adj[node][i].F] != comp_no)  continue;  
        color[adj[node][i].F] = true ^ color[node];
        if(!colorable(adj[node][i].F, comp_no, vis))    return false;
    }
    return true;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    int t;
    cin>>t;
    REP1(tc,t){
        initialise();
        solve();
        REPc(i,0,n) vis[i] = false, color[i] = false;
        REP1(i,n){
            if(vis[i])  continue;
            num_comp++;
            compress_bridge_comp(i, num_comp, vis);
        }
        REPc(i,0,n) vis[i] = false;
        REP1(i,n){
            temp[comp[i]] = i;
        }
        int res = 0;
        REP1(i,num_comp){
            if(!colorable(temp[i], i, vis)){
                res += comp_sizes[i];
            }
        }
        /* REP1(i,n){
            cout<<i<<": "<<comp[i]<<endl;  
        } */
        cout<<"Case "<<tc<<": "<<res<<'\n';
    }
    return 0;
}
