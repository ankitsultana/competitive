/* Author: Ankit Sultana
 * Problem id: 1096
 * * * * * * * * * */
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#define LL long long
#define mod 10007

using namespace std;

/* Matrix Expo Code */
#define SIZE 4
int T[SIZE][SIZE], orig_T[SIZE][SIZE], dummy[SIZE][SIZE];
vector<int> fnot;	// Should have size == SIZE

void init(int a, int b, int c) {
	std::fill(&T[0][0], &T[0][0] + SIZE*SIZE, 0);
	T[0][1] = 1, T[1][2] = 1, T[2][3] = 1, T[3][3] = 1;
	T[2][0] = b, T[2][2] = a;
	std::copy(&T[0][0], &T[0][0] + SIZE*SIZE, &orig_T[0][0]);
	fnot.clear();
	for(int i = 0; i < 4; i++)
		fnot.push_back(0);
	fnot[3] = c;
}
template<typename T>
void mul(T a[], T b[], T c[]) {
	std::fill(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, 0);
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			for(int k = 0; k < SIZE; k++) {
				dummy[i][j] += (a[i][k] * b[k][j]) % mod;
				if(dummy[i][j] > mod)
					dummy[i][j] -= mod;
			}
		}
	}
	std::copy(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, &c[0][0]);
}
int temp[SIZE][SIZE];
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
int solve(S n) {	// return f(n)
	std::copy(&orig_T[0][0], &orig_T[0][0] + SIZE*SIZE, &T[0][0]);
	matrix_expo(T, n, T);
	int answer = 0;
	for(int i = 0; i < SIZE; i++) {
		answer += (T[0][i] * fnot[i]) % mod;
		if(answer > mod)
			answer -= mod;
	}
	return answer;
}
/* End Matrix Expo */


int main() {
	ios_base::sync_with_stdio(false);  
	int t, a, b, c, n;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n >> a >> b >> c;
		init(a, b, c);
		cout << "Case " << tc << ": " << solve(n) << '\n';
	}
	return 0;
}
