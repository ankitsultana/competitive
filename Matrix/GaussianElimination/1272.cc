/* Author: Ankit Sultana
 * Problem Name: Maximum Subset Sum (1272)
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#define LL long long
using namespace std;

const int N = 63, MAXN = 103;
LL arr[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        sort(arr, arr + n, greater<LL>());
        for(int b = N-1, row = 0; b >= 0 and row < n; b--) {
            if(((1ll << b) & arr[row]) == 0ll) {
                int f = -1;
                for(int i = row+1; i < n; i++) {
                    if((1ll << b) & arr[i]) { f = i;  break; }
                }
                if(f == -1) continue;
                swap(arr[row], arr[f]);
            }
            for(int i = row+1; i < n; i++) {
                if((1ll << b) & arr[i]) arr[i] ^= arr[row];
            }
            row++;
        }
        LL res = 0;
        for(int i = 0; i < n; i++) if((res ^ arr[i]) > res) res ^= arr[i];
        cout << res << '\n';
    }
    return 0;
}
