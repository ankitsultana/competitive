/* Author: Ankit Sultana
 * Problem Name: Circle in Square (1022)
 * * * * * * * * * */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int t;
    double PI = acos(0.0) * 2ll, r;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cin >> r;
        double answer = (4.00l*r*r) - (PI * (r) * (r));
        cout << "Case " << tc << ": " << fixed << setprecision(2) << answer << '\n';
    }
    return 0;
}
