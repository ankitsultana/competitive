/* Author: Ankit Sultana
 * Problem id: 1214
 * * * * * * * * * */
#include <iostream>
#define LL long long

using namespace std;

bool trial(string &a, LL b) {
	int size = a.size();
	LL buffer = 0;
	for(int iter = 0; iter < size; iter++) {
		buffer = buffer*10 + (a[iter] - '0');
		buffer = buffer % b;
	}
	return buffer == 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	string a;
	LL b;
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		string res = "not divisible";
		cin >> a >> b;
		if(b < 0)	b = -b;
		if(a[0] == '-')	a = a.substr(1);
		if(trial(a, b))	res = "divisible";
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;  
}
