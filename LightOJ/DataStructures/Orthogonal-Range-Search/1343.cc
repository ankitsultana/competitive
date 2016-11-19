#include <bits/stdc++.h>
#define gc getchar_unlocked
using namespace std;
template <typename T> void in(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

const int MAXN = 503;
unsigned int dp[MAXN][MAXN];
unsigned int bit[MAXN][MAXN];
int arr[MAXN];
int n;

void update_y(int x, int y, unsigned int val) {
    while(y <= n) {
        bit[x][y] += val;
        y += y & -y;
    }
}
void update(int x, int y, unsigned int val) {
    while(x > 0) {
        update_y(x, y, val);
        x -= x & -x;
    }
}
unsigned int query_y(int x, int y) {
    unsigned int res = 0;
    while(y > 0) {
        res += bit[x][y];
        y -= y & -y;
    }
    return res;
}
unsigned int query(int x, int y) {
    if(y <= x) return 0u;
    unsigned int res = 0;
    while(x <= n) {
        res += query_y(x, y);
        x += x & -x;
    }
    return res;
}

void init() {
    for(int i = 0; i < MAXN; i++) {
        for(int j = 0; j < MAXN; j++) {
            bit[i][j] = 0u;
            dp[i][j] = 0u;
        }
    }
}

struct event {
    int l, r, sum;
    bool operator<(const event &other) const {
        return sum == other.sum ? (r - l + 1) > (other.r - other.l + 1) : sum < other.sum;
    };
};

int main() {
    int t;
    in(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        in(n);
        for(int i = 1; i <= n; i++) {
            in(arr[i]);
        }
        init();
        unsigned res = 0;
        vector<event> v;
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n; j++) {
                v.push_back({i, j, arr[i] + arr[j]});
            }
        }
        sort(v.begin(), v.end());
        for(int i = 0; i < v.size(); i++) {
            event& seg = v[i];
            dp[seg.l][seg.r] = query(seg.l + 1, seg.r - 1) + 1u;
            update(seg.l, seg.r, dp[seg.l][seg.r]);
            res += dp[seg.l][seg.r];
        }
        printf("%u\n", res);
    }
    return 0;
}
