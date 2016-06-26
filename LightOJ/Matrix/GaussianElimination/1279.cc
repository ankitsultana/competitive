/* Author: Ankit Sultana
 * Problem Name: Graph Coloring (1279)
 */
#include <iostream>
#include <vector>
#define LL long long
using namespace std;
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T, typename S> T expo(T b, S e){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b), e>>1): (b*expo((b*b), e>>1));}
template<typename T, typename S> T modinv(T a, S mod) { return expo(a, mod-2, mod); }

const int MAXN = 103;
LL mod, MOD = 1e9 + 7;

/* Gauss for modular inverses
 */
template<typename T, typename S>
vector<vector<T> > gaussian(vector<vector<T> > m, S mod) {
    if(m.empty())   return { };
    int no_rows = m.size(), no_cols = m[0].size();
    for(int row = 0, col = 0; row < no_rows and col < no_cols; col++) {
        if(m[row][col] == 0) {
            int f = -1;
            for(int i = row+1; i < no_rows; i++) {
                if(m[i][col] != 0) { f = i; break; }
            }
            if(f == -1) continue;
            swap(m[f], m[row]);
        }
        for(int c = col+1; c < no_cols; c++) m[row][c] = (m[row][c] * modinv(m[row][col], mod)) % mod;
        m[row][col] = 1;
        for(int r = row+1; r < no_rows; r++) {
            T temp = m[r][col];
            for(int c = col; c < no_cols; c++) m[r][c] = (m[r][c] - ((m[row][c] * temp)%mod) + mod) % mod;
        }
        row++;
    }
    return m;
}
/* End Modular Gaussian
 */

int main() {
    ios_base::sync_with_stdio(false);
    int t, n, m, a, b;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cin >> n >> m >> mod;
        vector<vector<LL> > mat(n, vector<LL>(n+1, 0));
        vector<int> adj[MAXN];
        while(m--) {
            cin >> a >> b;
            a--, b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
            mat[a][b] = 1;
            mat[b][a] = 1;
        }
        for(int i = 0; i < n; i++)  mat[i][i] = -1;
        mat = gaussian(mat, mod);
        int rak = 0, total_var = n;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(mat[i][j]) {
                    rak++;
                    break;
                }
            }
        }
        int free_var = total_var - rak;
        LL res = expo(mod, free_var, MOD);
        cout << "Case " << tc << ": " << res << '\n';
    }
    return 0;
}
