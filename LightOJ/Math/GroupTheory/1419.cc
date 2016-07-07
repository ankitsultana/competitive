#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;

const LL mod = 1e9 + 7;

template<typename T> T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }

LL compute(LL n, LL k) {
    LL res = 0;
    for(LL i = 1; i <= n; i++) {
        res += expo(k, gcd(i, n), mod);
        res %= mod;
    }
    res = (res * modinv(n)) % mod;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n, k, t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cin >> n >> k;
        cout << "Case " << tc << ": " << compute(n, k) << '\n';
    }
    return 0;
}
