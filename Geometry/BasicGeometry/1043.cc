/* Author: Ankit Sultana
 * Problem Name: Triangle Partitioning (1043)
 * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        double ab, ac, bc, r;
        cout << "Case " << tc << ": ";
        cin >> ab >> ac >> bc >> r;
        double res = ab * sqrt(1.00l/(1.00l + (1.00l/r)));
        cout << fixed << setprecision(8) << res << '\n';
    }
    return 0;
}
