/* Author: Ankit Sultana
 * Problem id: 1163
 * * * * * * * * * */
#include <iostream>
#include <vector>
#include <limits>
#define LL long long

using namespace std;
#define INF std::numeric_limits<LL>::max()

int main() {
	ios_base::sync_with_stdio(false);
	LL n;
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		LL lower = 0, upper = INF, mid;
		while(upper > lower) {
			mid = (upper - lower)/2 + lower;  
			if(mid - mid/10 >= n) {
				upper = mid;
			} else {
				lower = mid+1;  
			}
		}
		while((lower-1) - (lower-1)/10 == n) {
			lower--;  
		}
		cout << "Case " << tc << ": ";
		vector<LL> result;
		while(lower - lower/10 == n) {
			result.push_back(lower);
			lower++;
		}
		for(int i = 0; i < result.size(); i++) {
			if(i == result.size()-1) {
				cout << result[i];  
			} else {
				cout << result[i] << ' ';  
			}
		}
		cout << '\n';
	}
	return 0;
}
