/* Author: Ankit Sultana
 * Problem Name: Aladdin and the Magical Lamp (1347)
 */
#include <cstdio>
#include <algorithm>
#include <string>
#include <cassert>
#include <vector>
#include <cstdint>
using namespace std;

template<typename T, typename Compare = std::less<T> >
struct sparse_table {
    int n;
    vector<vector<T> > dp;
    template<typename iter>
    void build(iter a, iter b) {
        iter temp = a;
        int size = b - a, i, j, upper;
        dp.resize(size);
        int l = __log2(size);
        for(i = 0; i < size; i++) dp[i].resize(l+1);
        for(i = 0; i < size; i++, temp++) dp[i][0] = *temp;
        for(i = 1; i <= l; i++) {
            upper = size - (1<<(i-1));
            for(j = 0; j < upper; j++) dp[j][i] = __min(dp[j][i-1], dp[j + (1<<(i-1))][i-1]);
            for(; j < size; j++)    dp[j][i] = dp[j][i-1];
        }
    }
    T query(int i, int j) { // return min/max in range i..j (0 based)
        if(i == j)  return dp[i][0];
        int l = __log2(j - i);
        return __min(dp[i][l], dp[j - (1<<l) + 1][l]);
    }
private:
    const int tab32[32] = {0,9,1,10,13,21,2,29,11,14,16,18,22,25,3,30,8,12,20,28,15,17,24,7,19,27,23,6,26,5,4,31};
    int __log2(int x) { return x |= x >> 1, x |= x >> 2, x |= x >> 4, x |= x >> 8, x |= x >> 16, tab32[(uint32_t)(x*0x07C4ACDD) >> 27]; }
    inline int __min(int a, int b) { return b + ((a-b) & (a-b)>>31); }
};

struct suffix_array {
    const static int __MAXN = 1e5 + 1000;
    int lcp[__MAXN], cnt[256], cls[2][__MAXN], pos[2][__MAXN], st[__MAXN], rnk[__MAXN], size;
    int arr[__MAXN];
    string s;
    suffix_array() : size(0) { }
    void clear() {
        for(int i = 0; i < size; i++)
            lcp[i] = cls[0][i] = cls[1][i] = pos[0][i] = pos[1][i] = st[i] = rnk[i] = 0;
        size = 0;
        s.clear();
    }
    void build(string &s) {
        if(size == 0)   clear();
        this->s = s;
        this->size = s.size();
        int i, j;
        fill(cnt, cnt + sizeof(cnt), 0);
        int n = s.size();
        for (i = 0; i < n; i++) { cnt[s[i]] ++; cls[0][i] = s[i];}
        for (i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
        for (i = 0; i < n; i++) pos[0][--cnt[cls[0][i]]] = i;
        int cur = 0;
        for (i = 0; (1 << i) < n; i++) {
            int clen = (1 << i);
            for (j = 0; j < n; j++) {
                if (j > 0 && pos[cur][j - 1] + clen < n && cls[cur][pos[cur][j]] == cls[cur][pos[cur][j - 1]] &&
                    cls[cur][pos[cur][j] + clen / 2] == cls[cur][pos[cur][j - 1] + clen / 2]
                   )
                    cls[1 - cur][pos[cur][j]] = cls[1 - cur][pos[cur][j - 1]];
                else cls[1 - cur][pos[cur][j]] = j;
            }
            for (j = 0; j < n; j++) { st[j] = j; pos[1 - cur][j] = pos[cur][j]; }
            for (j = 0; j < n; j++) {
                int cele = pos[cur][j] - clen;
                if (cele >= 0) pos[1 - cur][st[cls[1 - cur][cele]]++] = cele;
            }
            cur = 1 - cur;
        }
        for (i = 0; i < n; i++) { pos[0][i] = pos[cur][i]; rnk[pos[cur][i]] = i;}
        int x = 0;
        for (i = 0; i < n; i++) {
            if (rnk[i] < n - 1) {
                for (j = pos[cur][rnk[i] + 1]; __max(i, j) + x < n && s[i + x] == s[j + x]; x++);
                lcp[rnk[i] + 1] = x; if (x > 0) x--;
            }
        }
        for(int i = 0; i < n; i++) arr[i] = pos[1][i];
    }
    sparse_table<int> s_t;
    int lcs(vector<string> &l, vector<int> &lens) {
        int num = l.size(), res = 0;
        s_t.build(lcp, lcp + size);
        auto get_idx = [&](int x) {
            int res = lower_bound(lens.begin(), lens.end(), arr[x]) - lens.begin();
            return lens[res] == arr[x] ? res + 1 : res;
        };
        int counter[10] = {0}, total_cnt = 0;
        int low = 1, high = 1;
        counter[get_idx(low)]++;
        //for(int i = 1; i < size; i++) {
            //cout << i << " : " << (get_idx(i)) << " lcp = " << lcp[i] << endl;
        //}
        total_cnt = 1;
        while(high < size) {
            while(high < size && total_cnt < num) {
                high++;
                if(high == size)    return res;
                if(++counter[get_idx(high)] == 1)  total_cnt++;
            }
            while(low < high && total_cnt == num) {
                //cout << low << ' ' << high << endl;
                res = max(res, s_t.query(low + 1, high));
                if(--counter[get_idx(low)] == 0)   total_cnt--;
                low++;
            }
        }
        return res;
    }
private:
    inline int __max(int a, int b) { return a - ((a-b) & (a-b)>>31); }
};

suffix_array tester;
string concat;

int n;
vector<string> arr;
char cache[10003];

int main() {
    int t;
    string buffer = "9876543210";
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        vector<int> lens;
        n = 3;
        arr.resize(n);
        for(int i = 0; i < n; i++) {
            scanf("%s", cache);
            arr[i] = string(cache);
            concat += arr[i];
            concat.push_back(buffer[i]);
            lens.push_back(concat.size() - 1);
        }
        tester.build(concat);
        printf("Case %d: %d\n", tc, tester.lcs(arr, lens));
        tester.clear();
        concat.clear();
    }
    return 0;
}
