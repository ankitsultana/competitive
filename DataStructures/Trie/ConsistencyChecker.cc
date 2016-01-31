/* Author: Ankit Sultana
 * Problem id: 1129
 * * * * * * * * * */
#include <iostream>
#define MAXN 10003

using namespace std;
int trie_size, n;
struct node {
	bool end, pres;
	int next[10];
	void reset() {
		end = false;
		pres = false;
		for(int i = 0; i < 10; i++)
			next[i] = 0;
	}
}trie[20*MAXN];

bool insert(int root, const string &word, int size, int idx = 0) {
	if(trie[root].end) {
		return false;  
	} else if(idx == size) {
		if(trie[root].pres)	return false;
		trie[root].end = true;
		trie[root].pres = true;
		return true;
	}
	trie[root].pres = true;
	int n = word[idx] - '0';
	if(trie[root].next[n] == 0) {
		trie[root].next[n] = ++trie_size;
		trie[trie_size].reset();
	}
	return insert(trie[root].next[n], word, size, idx+1);
}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	for(int tc = 1; tc <= t; tc++) {
		bool check = true;
		string temp;
		cin >> n;
		trie[1].reset();
		trie_size = 1;
		while(n--) {
			cin >> temp;
			check &= insert(1, temp, temp.size());
		}
		cout << "Case " << tc << ": ";
		if(check) {
			cout << "YES\n";
		} else {
			cout << "NO\n";  
		}
	}
	return 0;
}
