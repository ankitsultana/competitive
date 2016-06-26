/* Author: Ankit Sultana
 * Problem Name: Baker Vai (1071)
 * * * * * * * * * */
#include <iostream>
#include <algorithm>
#define MAXN 102

using namespace std;
int dp[MAXN][MAXN][MAXN], n, m;
int grid[MAXN][MAXN];

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n >> m;
		for(int r = 1; r <= n; r++) {
			for(int c = 1; c <= m; c++) {
				cin >> grid[r][c];
			}
		}
		dp[1][1][1] = 0;
		dp[1][1][2] = grid[1][1] + grid[1][2];
		for(int c = 3; c <= m; c++)
			dp[1][1][c] = dp[1][1][c-1] + grid[1][c];
		for(int r = 2; r <= n; r++) {
			for(int c = 1; c < m; c++) {
				for(int x = c+1; x <= m; x++) {
					dp[r][c][x] = dp[r-1][c][x] + grid[r][c] + grid[r][x];
				}
			}
			for(int c = 2; c < m; c++) {
				for(int x = c+1; x <= m; x++) {
					dp[r][c][x] = max(dp[r][c][x], dp[r][c-1][x] + grid[r][c]);
				}
			}
			for(int c = 1; c < m; c++) {
				for(int x = c+2; x <= m; x++) {
					dp[r][c][x] = max(dp[r][c][x], dp[r][c][x-1] + grid[r][x]);
				}
			}
		}
		cout << "Case " << tc << ": " << dp[n][m-1][m] << '\n';
	}
	return 0;
}
