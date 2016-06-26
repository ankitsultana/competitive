/* Author: Ankit Sultana
 * Problem id: 1045
 * * * * * * * * * */
#include <iostream>
#include <cmath>
#define MAXN 1000002
#define MAXB 1002

using namespace std;
double num[MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	int t, n, b;
	cin >> t;
	// Precompute num[i]
	num[2] = log10(2.00l);
	for(int i = 3; i < MAXN; i++) {
		num[i] = num[i-1] + log10((double)i);  
	}
	for(int tc = 1; tc <= t; tc++) {
		double res;
		cin >> n >> b;
		if(n < 2) {
			res = 1.0l;
		} else {
			res = num[n]/log10((double)b) + 1.00l;
		}
		cout << "Case " << tc << ": " << (long long)res << '\n';
	}
	return 0;
}
