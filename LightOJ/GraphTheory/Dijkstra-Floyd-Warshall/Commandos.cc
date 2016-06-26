/* Author: Ankit Sultana
 * Problem id: 1174
 * * * * * * * * * */
#include <stdio.h>
#include <algorithm>
#define MAXN 103
#define INF 1<<28
#define gc getchar_unlocked
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x; }

using namespace std;
int dp[MAXN][MAXN];

int main() {
	int t, n, a, b, m, sc, sink;
	scanint(t);
	for(int tc = 1; tc <= t; tc++) {
		printf("Case %d: ", tc);
		scanint(n);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				dp[i][j] = INF;
		scanint(m);
		while(m--) {
			scanint(a), scanint(b);  
			dp[a][b] = 1;
			dp[b][a] = 1;
		}
		scanint(sc), scanint(sink);
		for(int mid = 0; mid < n; mid++) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(i == j) {
						dp[i][j] = 0;  
					} else if(dp[i][mid] != INF && dp[mid][j] != INF) {
						dp[i][j] = min(dp[i][j], dp[i][mid] + dp[mid][j]);
					}
				}
			}
		}
		int res = 0;
		for(int i = 0; i < n; i++) {
			res = max(res, dp[sc][i] + dp[i][sink]);
		}
		printf("%d\n", res);
	}
	return 0;
}
