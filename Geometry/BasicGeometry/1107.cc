/* Author: Ankit Sultana
 * Problem Name: How Cow (1107)
 * * * * * * * * * * * * * * * */
#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        int x1, x2, y1, y2, x, y, q;
        cout << "Case " << tc << ":\n";
        cin >> x1 >> y1 >> x2 >> y2;
        cin >> q;
        while(q--) {
            cin >> x >> y;
            if(x >= x1 and x <= x2 and y >= y1 and y <= y2) {
                cout << "Yes\n";
            } else {
                cout << "No\n";
            }
        }
    }
    return 0;
}
