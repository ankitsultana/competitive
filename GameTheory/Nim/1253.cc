/* Author: Ankit Sultana
 * Problem Name: Misere Nim (1253)
 */
#include <iostream>
#define MAXN 103

using namespace std;
int n, arr[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        cin >> n;
        bool flag = true;
        int res = 0;
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
            if(arr[i] > 1)  flag = false;
            res ^= arr[i];
        }
        if(flag) {
            cout << (n % 2 == 1 ? "Bob" : "Alice") << '\n';
        } else {
            cout << (res == 0 ? "Bob" : "Alice") << '\n';
        }
    }
    return 0;
}
