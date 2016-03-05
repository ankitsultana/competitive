/* Author: Ankit Sultana
 * Problem id: 1234
 * * * * * * * * * */
#include <stdio.h>
#include <iostream>
#include <algorithm>
#define MAXN 10003

using namespace std;

pair<int, int> input[MAXN];
double answer[MAXN];

int main() {
	int n, t;
	scanf("%d", &t);
	for(int tc = 1; tc <= t; tc++) {
		scanf("%d", &n);
		input[tc].first = n, input[tc].second = tc;
	}
	sort(input + 1, input + t + 1);
	int iter = 1;
	double res = 0;
	while(iter <= input[1].first) {
		res += 1.0l/(double)iter;
		iter++;  
	}
	answer[input[1].second] = res;
	for(int x = 2; x <= t; x++) {
		while(iter <= input[x].first) {
			res += 1.0l/iter;
			iter++;
		}
		answer[input[x].second] = res;
	}
	for(int tc = 1; tc <= t; tc++) {
		printf("Case %d: %.9lf\n", tc, answer[tc]);  
	}
		// printf("Case %d: %lf\n", tc, res);  
	return 0;  
}
