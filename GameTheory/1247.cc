/* Author: Ankit Sultana
 * Problem Name: Matrix Game (1247)
 */
#include <iostream>
#define LL long long
#define MAXN 53

using namespace std;

int total[MAXN], grid[MAXN][MAXN], n, m;

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        cin >> n >> m;
        for(int i = 0; i < n; i++) {
            total[i] = 0;
            for(int j = 0; j < m; j++) {
                cin >> grid[i][j];
                total[i] += grid[i][j];
            }
        }
        LL res = 0;
        for(int i = 0; i < n; i++) {
            res ^= total[i];
        }
        if(res == 0) {
            cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
    }
    return 0;
}
