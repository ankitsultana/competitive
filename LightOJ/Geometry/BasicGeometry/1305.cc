/* Author: Ankit Sultana
 * Problem Name: Area of a parallelogram (1305)
 * * * * * * * * * */
#include <iostream>
#include <iomanip>
#include <cmath>
#define LL long long

using namespace std;

struct point {
    LL x, y;
};

LL p_area(point a, point b, point c) {
    return abs((a.x - b.x) * c.y + (b.x - c.x) * a.y + (c.x - a.x) * b.y);
}

int main() {
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        point a, b, c, d;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        d.x = a.x + c.x - b.x;
        d.y = a.y + c.y - b.y;
        cout << "Case " << tc << ": " << d.x << ' ' << d.y << ' ' << p_area(a, b, d) << '\n';
    }
    return 0;
}
