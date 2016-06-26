/* Author: Ankit Sultana
 * Problem Name: Left Right (1192)
 */
#include <iostream>
#define MAXN 103

using namespace std;
int one[MAXN], two[MAXN];
int n;

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cin >> n;
        int res = 0;
        for(int i = 0; i < n; i++) {
            cin >> one[i] >> two[i];
            res ^= two[i] - one[i] - 1;
        }
        cout << "Case " << tc << ": ";
        cout << (res == 0 ? "Bob" : "Alice") << '\n';
    }
    return 0;
}
