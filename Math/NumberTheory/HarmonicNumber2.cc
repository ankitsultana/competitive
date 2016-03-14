/* Author: Ankit Sultana
 * Problem id: 1245
 * * * * * * * * * */
#include <iostream>
#include <cmath>
#define LL long long

using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	LL n;
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		LL res = 0;
		cin >> n;
		LL rootn = sqrt(double(n)), d = 1;
		for(; d*d <= n; d++) {
			res += n/d;
		}
		LL x = n/d, lower, upper, freq;
		for(; x > 0; x--) {
			lower = (n/(x+1)) + 1;
			upper = n/x;
			freq = upper - lower + 1;
			res += x * freq;
		}
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
