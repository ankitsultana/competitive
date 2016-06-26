/* Author: Ankit Sultana
 * Problem id: 1109
 * * * * * * * * * */
#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 1003

using namespace std;
struct thing {
	int a, b;
	bool operator<(const thing &other) const {
		return b == other.b?a > other.a: b < other.b;
	}
};
vector<thing> arr;

int main() {
	ios_base::sync_with_stdio(false);
	for(int i = 1; i <= 1000; i++) {
		int cnt = 0;
		for(int j = 1; j <= i; j++) {
			if(i % j == 0) {
				cnt++;
			}
		}
		thing temp;
		temp.a = i, temp.b = cnt;
		arr.push_back(temp);
	}
	sort(arr.begin(), arr.end());
	int t, n;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		cout << "Case " << tc << ": " << arr[n-1].a << '\n';
	}
	return 0;
}
