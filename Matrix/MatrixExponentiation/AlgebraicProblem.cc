/* Author: Ankit Sultana
 * Problem id: 1070
 * * * * * * * * * */
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#define LL unsigned long long

using namespace std;
/* Matrix Expo Code */
#define SIZE 2
LL T[SIZE][SIZE], orig_T[SIZE][SIZE], dummy[SIZE][SIZE];
LL C[SIZE];
vector<LL> fnot;	// Should have size == SIZE

// copy to orig_T
void init(LL a, LL b) {
	fnot.clear();
	fnot.push_back(a);
	fnot.push_back(2);
	T[0][0] = a, T[0][1] = -b;
	T[1][0] = 1, T[1][1] = 0;
	std::copy(&T[0][0], &T[0][0] + SIZE*SIZE, &orig_T[0][0]);
}
template<typename T>
void mul(T a[], T b[], T c[]) {
	std::fill(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, 0);
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				dummy[i][j] = dummy[i][j] + (a[i][k] * b[k][j]);
	std::copy(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, &c[0][0]);
}
LL temp[SIZE][SIZE];
template<typename T>
void matrix_expo(T a[], int e, T b[]) {
	std::copy(&a[0][0], &a[0][0] + SIZE*SIZE, &temp[0][0]);
	std::fill(&b[0][0], &b[0][0] + SIZE*SIZE, 0);
	for(int i = 0; i < SIZE; i++)	b[i][i] = 1;
	while(e) {
		if(e&1)	mul(b, temp, b);
		e /= 2;
		mul(temp, temp, temp);
	}
}
template<typename S>
LL solve(S n) {	// return f(n)
	std::copy(&orig_T[0][0], &orig_T[0][0] + SIZE*SIZE, &T[0][0]);
	matrix_expo(T, n, T);
	LL answer = 0;
	for(int i = 0; i < fnot.size(); i++) {
		answer = answer + fnot[i] * T[0][i];  
	}
	// Compute answer
	return answer;
}
/* End Matrix Expo */
int main() {
	ios_base::sync_with_stdio(false);  
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		LL a, b, n;
		cin >> a >> b >> n;
		if(n == 0) {
			cout << "Case " << tc << ": " << 2 << '\n';
			continue;
		}
		init(a, b);
		cout << "Case " << tc << ": " << solve(n - 1) << '\n';
	}
	return 0;
}
