/* Author: Ankit Sultana
 * Problem id: 1220
 * * * * * * * * * */
#include <iostream>
#define LL long long

using namespace std;
int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		LL x;
		cin >> x;
		bool flag = x < 0;
		if(flag)	x = -x;
		LL res = -1;
		LL iter = 2;
		while(iter*iter <= x) {
			LL p = 0;
			while(x % iter == 0) {
				x /= iter;
				p++;
			}
			if(p > 0) {
				if(flag) {
					while(p % 2 == 0)
						p >>= 1;
					res = res == -1?p: min(res, p);
				} else {
					res = res == -1?p: min(res, p);
				}
			}
			iter++;
		}
		if(x > 1)	res = 1;
		if(res == -1)	res = 1;
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;  
}
