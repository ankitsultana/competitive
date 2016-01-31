/* Author: Ankit Sultana
 * Problem id: 1090
 * * * * * * * * * */
#include <iostream>
#define MAXN 1000003
#define LL long long

using namespace std;
LL pow2[MAXN], pow5[MAXN];	// powers of 2 and 5 in i!

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	pow2[0] = 0, pow5[0] = 0;
	for(int i = 1; i < MAXN; i++) {
		int temp = i;
		while(temp % 2 == 0) {
			pow2[i]++;
			temp /= 2;  
		}
		temp = i;
		while(temp % 5 == 0) {
			pow5[i]++;  
			temp /= 5;
		}
		pow2[i] += pow2[i-1];
		pow5[i] += pow5[i-1];
	}
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		int n, r, p, q;
		cin >> n >> r >> p >> q;
		LL total_pow2 = pow2[n] - pow2[n-r] - pow2[r] + ((pow2[p] - pow2[p-1]) * (LL)q);
		LL total_pow5 = pow5[n] - pow5[n-r] - pow5[r] + ((pow5[p] - pow5[p-1]) * (LL)q);
		LL answer = min(total_pow2, total_pow5);
		cout << "Case " << tc << ": " << answer << '\n';
	}
	return 0;
}
