#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
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
    const static int __MAXN = 1e5 + 1;
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
    template<typename iter>
    int cmp(iter a1, iter a2, iter b1, iter b2) {
        int a_size = a2 - a1, b_size = b2 - b1;
        int minim = __min(a_size, b_size);
        for(int i = 0; i < minim; i++, a1++, b1++) {
            if(*a1 < *b1) {
                return -1;
            } else if(*a1 > *b1) {
                return 1;
            }
        }
        if(a_size == b_size)
            return 0;
        return a_size < b_size ? -1 : 1;
    }
private:
    inline int __max(int a, int b) { return a - ((a-b) & (a-b)>>31); }
    inline int __min(int a, int b) { return b + ((a-b) & (a-b)>>31); }
};

int main() {
    return 0;
}
