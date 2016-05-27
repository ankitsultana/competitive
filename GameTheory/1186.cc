/* Author: Ankit Sultana
 * Problem Name: Incredible Chess (1186)
 */
#include <iostream>
#define MAXN 103

using namespace std;
int one[MAXN], two[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cin >> n;
        for(int i = 0; i < n; i++)  cin >> one[i];
        for(int i = 0; i < n; i++)  cin >> two[i], two[i] -= one[i] + 1;
        int res = 0;
        for(int i = 0; i < n; i++) {
            res ^= two[i];
        }
        cout << "Case " << tc << ": ";
        if(res == 0) {
            cout << "black wins\n";
        } else {
            cout << "white wins\n";
        }
    }
    return 0;
}
