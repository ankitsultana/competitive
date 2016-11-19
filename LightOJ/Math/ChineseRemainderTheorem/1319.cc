/* Author: Ankit Sultana
 * Problem Name: Monkey Tradition (1319)
 */
#include <bits/stdc++.h>
#define LL long long
#define FOR(i,c) for(__typeof(c.begin()) i = c.begin(); i != c.end(); i++)
#define F first
#define S second
using namespace std;

const LL mod = 1e9 + 7;

template<typename T> T gcd(T a, T b) { return b == 0?a: gcd(b, a % b); }
template<typename T> T LCM(T a, T b) { return a*(b/gcd(a, b)); }
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T, typename S> T expo(T b, S e){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b), e>>1): (b*expo((b*b), e>>1));}
template<typename T, typename S> T modinv(T a, S mod) { return expo(a, mod-2, mod); }
template<class T, class S> std::ostream& operator<<(std::ostream &os, const std::pair<T, S> &t) {
	os<<"("<<t.first<<", "<<t.second<<")";
	return os;
}
template<class T> std::ostream& operator<<(std::ostream &os, const std::vector<T> &t) {
	os<<"["; FOR(it,t) { if(it != t.begin()) os<<", "; os<<*it; } os<<"]";
	return os;
}

template<typename T>
T crt(vector<T> &as, vector<T> &mods) { // finds smallest positive x
    assert(as.size() == mods.size());
    T res = 0, total = 1;
    for(int i = 0; i < mods.size(); i++) total = (total * mods[i]);
    // for(auto &elem: mods) total = total * elem;
    for(int i = 0; i < mods.size(); i++) {
        res = (res + ((as[i] * modinv((total/mods[i]) % mods[i], mods[i])) % total) * (total/mods[i])) % total;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        cin >> n;
        vector<LL> mods(n), as(n);
        for(int i = 0; i < n; i++) {
            cin >> mods[i] >> as[i];
        }
        LL g = 1;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                g = max(g, gcd(mods[i], mods[j]));
            }
        }
        if(g > 1) {
            cout << "Impossible\n";
        } else {
            cout << crt(as, mods) << '\n';
        }
    }
    return 0;
}
