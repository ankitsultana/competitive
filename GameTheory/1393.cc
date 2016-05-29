/* Author: Ankit Sultana
 * Problem Name: Crazy Calendar (1393)
 */
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        int res = 0, temp, no_rows, no_cols;
        cin >> no_rows >> no_cols;
        for(int i = 0; i < no_rows; i++) {
            for(int j = 0; j < no_cols; j++) {
                int d = (no_rows - 1 - i) + (no_cols - 1 - j);
                cin >> temp;
                if(d % 2) {
                    res ^= temp;
                }
            }
        }
        cout << (res == 0 ? "lose" : "win") << '\n';
    }
    return 0;
}
