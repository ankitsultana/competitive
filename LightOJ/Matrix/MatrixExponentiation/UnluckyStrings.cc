/* Author: Ankit Sultana
 * Problem id: 1268
 * * * * * * * * * */
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#define LL long long

using namespace std;
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}

string alphabet;
string input;

/* Matrix Expo Code */
#define SIZE 51
unsigned T[SIZE][SIZE], orig_T[SIZE][SIZE], dummy[SIZE][SIZE];
vector<int> fnot;	// Should have size == SIZE

template<typename T>
void mul(T a[], T b[], T c[]) {
	std::fill(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, 0);
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			for(int k = 0; k < SIZE; k++) {
				dummy[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	std::copy(&dummy[0][0], &dummy[0][0] + SIZE*SIZE, &c[0][0]);
}
unsigned temp[SIZE][SIZE];
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
unsigned solve(S n) {	// return f(n)
	std::copy(&orig_T[0][0], &orig_T[0][0] + SIZE*SIZE, &T[0][0]);
	matrix_expo(T, n, T);
	unsigned answer = 0;
	for(int i = 0; i < fnot.size(); i++) {
		answer += T[0][i] * fnot[i];
	}
	return answer;
}
int P[300] = {0};

void prefix(const string &p) {
	int size = (int)p.size(), k = 0;
	P[0] = 0;
	for(int i = 1; i < size; i++) { 
		while(k > 0 && p[k] != p[i])
			k = P[k-1];  
		if(p[k] == p[i]) 
			k++;
		P[i] = k;
	}
}
void init() {
	std::fill(&T[0][0], &T[0][0] + SIZE*SIZE, 0);
	int size = input.size(), alp_size = alphabet.size();
	fnot = vector<int> (size, 1);
	prefix(input);
	// fnot done
	// prefix 0..i
	int k;
	for(int pre_size = 0; pre_size < size; pre_size++) {
		k = 0;
		// pattern is input, main_string is prefix of input
		// of size pre_size
		for(int i = 0; i < pre_size; i++) {
			while(k > 0 && input[k] != input[i]) {
				k = P[k-1];
			}
			if(input[k] == input[i])
				k++;
		}
		for(int c = 0; c < alp_size; c++) {
			// compute new_k 
			int new_k = k;
			while(new_k > 0 && input[new_k] != alphabet[c])
				new_k = P[new_k-1];
			if(input[new_k] == alphabet[c])
				new_k++;
			if(new_k < size) {
				T[pre_size][new_k]++;  
			}
		}
	}
	std::copy(&T[0][0], &T[0][0] + SIZE*SIZE, &orig_T[0][0]);
}
/* End Matrix Expo */


int main() {
	ios_base::sync_with_stdio(false);  
	int t;
	LL n;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		cin >> alphabet;
		cin >> input;
		init();
		unsigned res = solve(n);
		cout << "Case " << tc << ": " << res << '\n';
	}
	return 0;
}
