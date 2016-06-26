#include <iostream>
#include <vector>
#include <iomanip>
#define LL long long
using namespace std;
/* End Utilites
 */
/* Begin Gauss for doubles
 */
template<typename T>
vector<T> back_substitution(vector<vector<T> > m) {
    vector<T> vals(m[0].size() - 1, 0);
    for(int r = m.size() - 1; r >= 0; r--) {
        int f = -1;
        for(int c = 0; c < m[0].size() - 1; c++) {
            if(m[r][c]) {
                f = c; break;
            }
        }
        if(f != -1) {
            T rhs = m[r].back();
            for(int i = f+1; i < m[r].size() - 1; i++) {
                rhs -= m[r][i] * vals[i];
            }
            rhs /= m[r][f];
            vals[f] = rhs;
        }
    }
    return vals;
}
template<typename T>
vector<vector<T> > gaussian(vector<vector<T> > m) {
    if(m.empty())   return { };
    int no_rows = m.size(), no_cols = m[0].size();
    for(int row = 0, col = 0; row < no_rows and col < no_cols; col++) {
        if(m[row][col] == 0) {
            int f = -1;
            for(int i = row+1; i < no_rows; i++) {
                if(m[i][col] != 0) { f = i; break; }
            }
            if(f == -1) continue;
            swap(m[f], m[row]);
        }
        for(int c = col+1; c < no_cols; c++)  m[row][c] /= m[row][col];
        m[row][col] = 1;
        for(int r = row+1; r < no_rows; r++) {
            double temp = m[r][col];
            for(int c = col; c < no_cols; c++) {
                m[r][c] -= m[row][c] * temp;
            }
        }
        row++;
    } // m is now in Reduced Echelon
    return m;
}
template<typename T>
vector<vector<T> > inverse(vector<vector<T> > m) {
    vector<vector<T> > temp(m.size(), vector<T>(m[0].size() * 2, 0));
    for(int i = 0; i < m.size(); i++)   for(int j = 0; j < m[i].size(); j++)    temp[i][j] = m[i][j];
    for(int i = 0; i < m.size(); i++)   temp[i][i+m[i].size()] = 1;
    vector<vector<T> > x = gaussian(temp);
    vector<vector<T> > res = m;
    int n = m.size();
    for(int r = 0; r < n; r++) {
        for(int c = r+1; c < n; c++) {
            if(x[r][c]) {
                T crap = x[r][c];
                for(int i = c; i < 2*n; i++) {
                    x[r][i] -= crap * x[c][i];
                }
            }
        }
    }
    for(int i = 0; i < m.size(); i++)   for(int j = 0; j < m[i].size(); j++)    res[i][j] = x[i][j+m[i].size()];
    return res;
}
/* End Gauss for doubles
 */

int main() {
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        cin >> n;
        vector<pair<int, int> > arr(n);
        vector<vector<double> > mat(100, vector<double> (101, 0));
        bool infected[101] = {false};
        for(int i = 0; i < n; i++) {
            cin >> arr[i].first >> arr[i].second;
            arr[i].first--, arr[i].second--;
            infected[arr[i].first] = true;
        }
        for(int i = 0; i < 100; i++) {
            mat[i][i] = -1;
        }
        for(int i = 0; i < 99; i++) {
            if(!infected[i]) {
                for(int j = 1; j <= 6; j++) {
                    if(j + i > 99) {
                        mat[i][i] += 1.0l / 6;
                        continue;
                    }
                    mat[i][i+j] = 1.0l / 6;
                }
                mat[i][100] = -1;
            }
        }
        for(int i = 0; i < arr.size(); i++) {
            mat[arr[i].first][arr[i].second] = 1;
        }
        mat = gaussian(mat);
        vector<double> res = back_substitution(mat);
        cout << setprecision(6) << fixed << res[0] << '\n';
    }
    return 0;
}
