/* Author: Ankit Sultana
 * Problem id: 1336
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
		cin >> n;
		LL res =  n - (LL)sqrt(double(n)) - (LL)sqrt(double(n)/2.0l);
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
