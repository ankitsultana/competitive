/* Author: Ankit Sultana
 * Problem id: 1138
 * * * * * * * * * */
#include <iostream>
#define LL long long

using namespace std;

LL count(LL x) {
	LL res = 0, den = 5;
	while(den <= x) {
		res += x / den;
		den = den * 5ll;  
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	LL n, res;
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		LL higher = (LL)1e9, lower = 1, mid, temp;
		// find lower_bound
		while(higher > lower) {
			mid = (higher + lower) / 2;
			temp = count(mid);
			if(temp >= n) {
				higher = mid;
			} else if(temp < n) {
				lower = mid+1;  
			}
		}
		temp = count(higher);
		if(temp != n) {
			cout << "Case " << tc << ": " << "impossible" << '\n';
			continue;
		}
		cout << "Case " << tc << ": " << higher << '\n';
	}
	return 0;
}
