/* Author: Ankit Sultana
 * Problem id: 1002
 * Comment: This will give TLE due to changed dataset
 * * * * * * * * * */
#include <stdio.h>
#include <algorithm>
#define MAXN 503
#define gc getchar_unlocked
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x; }

using namespace std;
int dp[MAXN][MAXN];

int main() {
	int t, n, a, b, w, m;
	scanint(t);
	for(int tc = 1; tc <= t; tc++) {
		for(int i = 0; i < MAXN; i++) {
			for(int j = 0; j < MAXN; j++)
				dp[i][j] = -1;
			dp[i][i] = 0;
		}
		printf("Case %d:\n", tc);
		scanint(n), scanint(m);
		while(m--) {
			scanint(a), scanint(b), scanint(w);
			if(dp[a][b] > -1) {
				dp[a][b] = min(dp[a][b], w);
				dp[b][a] = min(dp[b][a], w);
			} else {
				dp[a][b] = w, dp[b][a] = w;
			}
		}
		for(int k = 0; k < n; k++) {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < n; j++) {
					if(dp[i][k] != -1 && dp[k][j] != -1) {
						if(dp[i][j] == -1)
							dp[i][j] = max(dp[i][k], dp[k][j]);
						else
							dp[i][j] = min(dp[i][j], max(dp[i][k], dp[k][j]));
					}
				}
			}
		}
		int sc;
		scanint(sc);
		for(int i = 0; i < n; i++) {
			if(i == sc)	{
				printf("0\n");
				continue;
			}
			if(dp[i][sc] == -1) {
				printf("Impossible\n");
			} else {
				printf("%d\n", dp[i][sc]);
			}
		}
	}
	return 0;
}
