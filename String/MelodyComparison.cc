/* Author: Ankit Sultana
 * Problem id: 1428
 * * * * * * * * * */
#include <iostream>
#include <algorithm>
#include <vector>
#define LL long long
#define MAXN 50003
#define MAXLOGN 19

using namespace std;

int P[MAXN] = {0};
vector<int> end_pts;
int shit;
struct suffix_array {
	int sa[MAXN][MAXLOGN], size;	// sa[i][log] is position of i-th suffix in lex order
	int arr[MAXN], log;	// arr[i] is the suffix at position i
	int sizess[MAXN];
	bool lower_case;
	string s;
	suffix_array(string s, bool lower_case = true): s(s), log(0) {
		this->size = s.size();
		this->lower_case = lower_case;
		preprocess();
	}
	void preprocess() {
		for(int i = 0; i < size; i++)	sa[i][0] = s[i] - (lower_case?'a': 'A');
		int cnt = 1;
		log = 0;
		for(int k = 1; (cnt >> 1) < size; k++, log++, cnt <<= 1) {
			for(int i = 0; i < size; i++) {
				events[i].a = sa[i][k-1], events[i].b = i + cnt < size?sa[i+cnt][k-1]: -1, events[i].idx = i;
			}
			sort(events, events + size);
			for(int i = 0; i < size; i++) {
				if(i > 0 && events[i].a == events[i-1].a && events[i].b == events[i-1].b) {
					sa[events[i].idx][k] = sa[events[i-1].idx][k];
				} else {
					sa[events[i].idx][k] = i;
				}
			}
		}
		for(int i = 0; i < size; i++) {
			arr[sa[i][log]] = i;
			sizess[sa[i][log]] = size - i;
		}
	}
	int lcp(int x, int y) {		// of [x..n) and [y..n)
		if(x > y)	swap(x, y);
		int res = 0;
		for(int i = log; i > -1; i--) {
			if(sa[x][i] == sa[y][i]) {
				res += min(1<<i, min(size - y, size - x));
				x += 1<<i, y += 1<<i;
				if(x >= size || y >= size)	break;
			}
		}
		return res;
	}
	struct event {
		int a, b, idx;
		bool operator<(const event &other) const {
			return a == other.a?b < other.b: a < other.a;
		}
	}events[MAXN];
	void printer() {
		for(int i = 0; i < size; i++) {
			cout << arr[i] << ' ';
		} cout << endl;
	}
	LL solve() {
		LL res = 0;
		for(int i = 0; i < size; i++) {
			int max_idx = (int)(upper_bound(end_pts.begin(), end_pts.end(), arr[i] + shit - 2) - end_pts.begin());
			if(max_idx == end_pts.size()) {
				max_idx = size;
			} else {
				max_idx = *upper_bound(end_pts.begin(), end_pts.end(), arr[i] + shit - 2);  
			}
			LL temp = max_idx - arr[i] - (i > 0?lcp(arr[i], arr[i-1]): 0);
			if(temp > 0)	res += temp;
		}
		return res;
	}
};

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
void kmp(const string &main_string, const string &pattern) {
	prefix(pattern);
	int res = 0, main_size = int(main_string.size());
	int pattern_size = int(pattern.size());
	int k = 0;
	for(int i = 0; i < main_size; i++) {
		while(k > 0 && pattern[k] != main_string[i]){
			k = P[k-1];  
		}
		if(pattern[k] == main_string[i]){
			k++;  
		}
		if(k == pattern_size){
			end_pts.push_back(i);
			res++;
			k = P[k-1];  
		}
	}
}
int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		string a, b;
		cin >> a >> b;
		shit = b.size();
		end_pts.clear();
		kmp(a, b);
		suffix_array tester(a);
		cout << "Case " << tc << ": " << tester.solve() << '\n';
	}
	return 0;
}
