/* Author: Ankit Sultana
 * Problem Name: Parallelograph Counting (1058)
 * * * * * * * * * */
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
#define LL long long
#define MAXN 1001

using namespace std;

struct point {
    double x, y;
}points[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        int n;
        LL answer = 0;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> points[i].x >> points[i].y;
        }
        vector<pair<double, double> > res;
        for(int i = 0; i < n; i++) {
            for(int j = i+1; j < n; j++) {
                res.push_back({ (points[i].x+points[j].x) / 2, (points[i].y+points[j].y) / 2});
            }
        }
        sort(res.begin(), res.end());
        LL cnt = 1, iter = 1;
        while(iter < res.size()) {
            while(iter < res.size() && res[iter] == res[iter-1]) {
                cnt++;
                iter++;
            }
            answer += (cnt) * (cnt - 1) / 2;
            cnt = 1;
            iter++;
        }
        cout << "Case " << tc << ": " << answer << '\n';
    }
    return 0;
}
