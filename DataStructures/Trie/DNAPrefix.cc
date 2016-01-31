/* Author: Ankit Sultana
 * Problem id: 1224
 * * * * * * * * * */
#include <iostream>
#define MAXN 50002

using namespace std;
int util[200];

int n, trie_size = 0;
int answer = 0;

struct node {
	int cnt;
	int next[4];
	void reset() {
		cnt = 0;
		for(int i = 0; i < 4; i++)
			next[i] = 0;
	}
}trie[50*MAXN];

void insert(int root, const string &word, int size, int idx = 0) {
	trie[root].cnt++;
	if(idx == size)
		return ;
	int temp = util[word[idx]];
	if(trie[root].next[temp] == 0) {
		trie[root].next[temp] = ++trie_size;
		trie[trie_size].reset();
	}
	insert(trie[root].next[temp], word, size, idx+1);
}

void go(int root, int d = 0) {
	answer = max(answer, d*trie[root].cnt);
	for(int i = 0; i < 4; i++) {
		if(trie[root].next[i] != 0) {
			go(trie[root].next[i], d+1);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	util['A'] = 0, util['G'] = 1, util['C'] = 2, util['T'] = 3;
	for(int tc = 1; tc <= t; tc++) {
		cin >> n;
		answer = 0;
		trie_size = 1;
		trie[1].reset();
		string temp;
		while(n--) {
			cin >> temp;
			insert(1, temp, temp.size());
		}
		go(1);
		cout << "Case " << tc << ": " << answer << '\n';
	}
	return 0;
}
