#include <iostream>
#include <vector>
#include <bitset>
#define LL long long
using namespace std;
const LL mod = 1e9 + 7;
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}

const int MAXN = 1e3+1;
vector<LL> primes;

void pre() {
    for(int i = 2; i < 300; i++) {
        bool flag = true;
        for(int j = 2; j < i; j++)
            if(i % j == 0) {
                flag = false; break;
            }
        if(flag)    primes.push_back(i);
    }
}

const int BT = 1003;
void gaussian(vector<bitset<BT> > a, int no_rows, int no_cols) {
    for(int row = 0, col = 0; row < no_rows and col < no_cols; col++) {
        if(!a[row][col]) {
            int f = -1;
            for(int r = row+1; r < no_rows; r++) {
                if(a[r][col]) { f = r; break; }
            }
            if(f == -1) continue;
            swap(a[f], a[row]);
        }
        for(int r = row+1; r < no_rows; r++) {
            if(a[r][col]) a[r] ^= a[row];
        }
        row++;
    }
    int total_var = no_cols - 1, rak = 0;
    for(int i = 0; i < no_rows; i++)
        if(a[i].count())    rak++;
    int free_var = total_var - rak;
    cout << expo(2ll, free_var, mod) - 1 << '\n';
}

LL arr[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    pre();
    int t, n;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case " << tc << ": ";
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        vector<bitset<BT> > a(primes.size());
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < primes.size(); j++) {
                int cnt = 0;
                while(arr[i] % primes[j] == 0) {
                    arr[i] /= primes[j], cnt++;
                }
                a[j].set(i, cnt % 2);
            }
        }
        gaussian(a, primes.size(), n + 1);
    }
    return 0;
}
