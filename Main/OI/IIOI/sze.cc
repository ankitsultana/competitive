#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

const int MAXN = 1e4 + 3;
typedef pair<pair<double, double>, int> pt;
pt arr[MAXN];

struct comp {
    bool operator()(const pt &lhs, const pt &rhs) const {
        return lhs.F.F/lhs.F.S > rhs.F.F/rhs.F.S;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arr[i].F.F >> arr[i].F.S;
        arr[i].S = i + 1;
    }
    sort(arr, arr + n, comp());
    for(int i = 0; i < n; i++) {
        cout << arr[i].S << '\n';
    }
    return 0;
}
