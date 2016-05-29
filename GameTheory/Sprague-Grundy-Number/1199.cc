/* Author: Ankit Sultana
 * Problem Name: Partitioning Game (1199)
 */
#include <iostream>
#include <cassert>
#include <vector>
#define MAXN 10003

using namespace std;
int gnd[MAXN];
bool vis[MAXN] = {false};

int mex(vector<int> v) {
    for(int i = 0; i < v.size(); i++)
        vis[v[i]] = true;
    int res = -1;
    for(int i = 0; i < MAXN; i++)
        if(!vis[i]) {
            res = i;
            break;
        }
    for(int i = 0; i < v.size(); i++)
        vis[v[i]] = false;
    return res;
}

void go() {
    gnd[1] = 0;
    gnd[2] = 0;
    for(int i = 3; i < MAXN; i++) {
        vector<int> temp;
        for(int one = 1, two = i - 1; one < two; one++, two--) {
            temp.push_back(gnd[one] ^ gnd[two]);
        }
        gnd[i] = mex(temp);
        assert(gnd[i] >= 0);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    go();
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cin >> n;
        int res = 0, temp;
        for(int i = 0; i < n; i++) {
            cin >> temp;
            res ^= gnd[temp];
        }
        cout << "Case " << tc << ": ";
        cout << (res != 0 ? "Alice" : "Bob") << '\n';
    }
    return 0;
}
