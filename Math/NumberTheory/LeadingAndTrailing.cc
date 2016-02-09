/* Author: Ankit Sultana
 * Problem id: 1282
 * * * * * * * * * */
#include <iostream>
#include <cmath>
#include <iomanip>
#define LL long long

using namespace std;
template<typename T> T expo(T b, T e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T, typename S> T expo(T b, S e){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b), e>>1): (b*expo((b*b), e>>1));}

void adjust(double &a) {
	int dgts = (int)(log10(a)) + 1;
	if(dgts > 3) {
		double divide = expo(10ll, dgts - 3);
		a /= divide;
	}
}

template<typename T>
double d_expo(double b, T e) {
	double res = 1.00l;
	while(e) {
		if(e&1) {
			res = res * b;
			adjust(res);
			// adjust
		}
		b = b*b;
		adjust(b);
		// adjust
		e >>= 1;  
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		LL n, one = -1, two, k;
		cin >> n >> k;
		two = expo(n, k, 1000ll);
		two %= 1000ll;
		double temp = d_expo((double)n, k);
		one = (int)(temp);
		// two done
		cout << "Case " << tc << ": " << one << ' ' << setfill('0') << setw(3) << two << '\n';
	}
	return 0;
}
