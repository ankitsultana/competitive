/* Author: Ankit Sultana
 * Problem Name: Minimum Arc Distance (1433)
 * * * * * * * * * */
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double normalize(double x) {
    if(x < -1.0)    x = -1.0;
    else if(x > 1.0) x = 1.0;
    return x;
}

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        double answer, theta, radius, prod, dot;
        double ox, oy, ax, ay, bx, by;
        cin >> ox >> oy >> ax >> ay >> bx >> by;
        radius = sqrt((ox - ax) * (ox - ax) + (oy - ay) * (oy - ay));
        prod = sqrt((ox-ax)*(ox-ax) + (oy-ay)*(oy-ay)) * sqrt((ox-bx)*(ox-bx) + (oy-by)*(oy-by));
        dot = (ox-ax)*(ox-bx) + (oy-ay)*(oy-by);
        if(prod == 0.00) {
            theta = 0;
        } else {
            theta = acos(normalize(dot/prod));
        }
        answer = theta * radius;
        cout << "Case " << tc << ": " << fixed << setprecision(5) << answer << '\n';
    }
    return 0;
}
