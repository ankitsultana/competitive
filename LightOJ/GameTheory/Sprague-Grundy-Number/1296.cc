/* Author: Ankit Sultana
 * Problem Name: Again Stone Game (1296)
 */
#include <iostream>
#include <vector>
#define MAXN 1003

using namespace std;
int arr[MAXN];

int g(int x) {
    if(x <= 1)  return 0;
    else if(x % 2 == 0) return x/2;
    return g((x-1)/2);
}

int main() {
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        cin >> n;
        int res = 0, temp;
        for(int i = 0; i < n; i++) {
            cin >> temp;
            res ^= g(temp);
        }
        cout << (res == 0 ? "Bob" : "Alice") << '\n';
    }
    return 0;
}
