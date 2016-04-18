/* Author: Ankit Sultana
 * Problem Name: Guarding the Bananas (1203)
 * * * * * * * * * * * * * * * * * * * * * */
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>
#define LL long long
#define MAXN 100001

using namespace std;

const double PI = 2.00l * acos(0.00);

struct point {
    LL x, y, idx;
    bool operator<(const point &other) const {
        return x == other.x ? y < other.y: x < other.x;
    }
}points[MAXN];

double normalize(double x) {
    if(x > 1.0) x = 1.0;
    else if(x < -1.0) x = -1.0;
    return x;
}
double dist(point a, point b) {
    return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}
double get_angle(point o, point a, point b) {
    double prod = dist(o, a) * dist(o, b);
    double dot = (o.x-a.x)*(o.x-b.x) + (o.y-a.y)*(o.y-b.y);
    return acos(normalize(dot/prod));
}
double to_degree(double rad) {
    return rad * 180.00l / PI;
}
double cross(point o, point a, point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

vector<point> convexhull(point *f, point *e) {
    if(f == e) return { };
    else if(int(e - f) == 1) return vector<point>(1);
    sort(f, e);
    int n = int(e-f);
    vector<point> hull(2*n);
    int k = 0;
    point *temp;
    for(temp = f; temp != e; temp++) {
        while(k >= 2 && cross(hull[k-2], hull[k-1], *temp) <= 0) k--;
        hull[k++] = *temp;
    }
    temp = e, temp--;
    int t = k;
    do {
        temp--;
        while(k > t && cross(hull[k-2], hull[k-1], *temp) <= 0) k--;
        hull[k++] = *temp;
    } while(temp != f);
    hull.resize(k - (k > 1));
    return hull;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        double answer;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        vector<point> hull = convexhull(points, points + n);
        if(hull.size() > 2) {
            for(int c = 0; c < hull.size(); c++) {
                if(c == 0) {
                    answer = get_angle(hull[0], hull.back(), hull[1]);
                } else if(c == hull.size() - 1) {
                    answer = min(answer, get_angle(hull[c], hull[c-1], hull[0]));
                } else {
                    answer = min(answer, get_angle(hull[c], hull[c-1], hull[c+1]));
                }
            }
        } else {
            answer = 0;
        }
        cout << "Case " << tc << ": " << fixed << setprecision(8) << to_degree(answer) << '\n';
    }
    return 0;
}
