/* Author: Ankit Sultana
 * Problem Name: Calm Down (1072)
 * * * * * * * * * */
#include <iostream>
#include <iomanip>
#include <cmath>
#define LL long long

using namespace std;

int main() {
    int t;
    double PI = acos(0.0) * 2ll, R;
    LL n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cin >> R >> n;
        double theta = PI/double(n);
        double answer = R*sin(theta)/(1.00l + sin(theta));
        cout << "Case " << tc << ": " << fixed << setprecision(8) << answer << '\n';
    }
    return 0;
}
