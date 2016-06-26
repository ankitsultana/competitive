/* Author: Ankit Sultana
 * Problem id: 1098
 * * * * * * * * * */
#include <iostream>
#define LL long long

using namespace std;

inline LL range_sum(LL x, LL y) {
	return (y*(y+1)/2) - (x*(x-1)/2);  
}

int main() {
	ios_base::sync_with_stdio(false);
	LL n;
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		if(n < 3) {
			cout << "Case " << tc << ": 0\n";
			continue;
		}
		LL d = 2, res = 0;
		res = n*(n-1)/2;
		res--;
		res = -res;	// This is what is to be subtracted from result
		// for values n .. sqrt(n)
		for(; d*d <= n; d++) {
			res += (n/d)*d;
		}
		LL x = n/d, lower, upper, freq;
		for(; x > 0; x--) {
			lower = (n/(x+1))+1;
			upper = n/x;
			if(upper == n)	upper--;
			freq = upper - lower + 1;
			res += x * range_sum(lower, upper);
		}
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
