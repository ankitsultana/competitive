/* Author: Ankit Sultana
 * Problem id: 1144
 * * * * * * * * * */
#include <bits/stdc++.h>
#define LL long long
#define gc getchar_unlocked
using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}


const int MAXN = 1e6 + 3;
bool is_prime[MAXN];
int mu[MAXN];
void sieve_eratosthenes() {
	std::fill(&is_prime[0], &is_prime[0] + MAXN, true);
	is_prime[1] = false;
	for(int i = 2; i*i <= MAXN; i++){
		if(is_prime[i]){
			for(int j = i*i; j < MAXN; j += i){
				is_prime[j] = false;
			}
		}
	}
}
void compute_mu() {
    mu[1] = 1;
    for(int i = 2; i < MAXN; i++) {
        if(is_prime[i]) {
            mu[i] = -1;
            for(int j = MAXN/i; j > 1; j--) {
                if(j == i || j*i >= MAXN) continue;
                mu[j*i] = mu[j] * (-1);
            }
        }
    }
}

int main() {
    sieve_eratosthenes();
    compute_mu();
    int t, n, m;
    scanint(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        scanint(n), scanint(m);
        if(n == 0 and m == 0) {
            printf("%d\n", 0);
            continue;
        } else if(min(n, m) == 0) {
            printf("%d\n", 1);
            continue;
        }
        LL res = 2;
        for(int d = 1; d <= min(n, m); d++) {
            res += (LL) mu[d] * (n/d) * (m/d);
        }
        printf("%lld\n", res);
    }
    return 0;
}
