/* Author: Ankit Sultana
 * Problem Name: Points in Rectangle-II (1267)
 * * * * * * * * * */
#ifdef __APPLE__
	#include <iostream>
#endif
#include <stdio.h>
#include <cmath>
#include <cassert>
#include <map>
#include <vector>
#include <algorithm>
#define MID int mid = (l + r)>>1
#define LL long long
#define gc getchar_unlocked
#define MAXN 50003
using namespace std;
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}

struct point {
    int x, y;
    bool operator<(const point &other) const {
        return x < other.x;
    }
}points[MAXN];
struct event {
    int x, y1, y2, type, idx;
    bool operator<(const event &other) const {
        return x == other.x ? type > other.type : x < other.x;
    }
}events[MAXN*2];

int answer[MAXN];
int tree[MAXN*10];

void build_tree(int root, int l, int r) {
    if(l == r) {
        tree[root] = 0;
        return ;
    }
    MID;
    build_tree(root*2, l, mid);
    build_tree(root*2+1, mid+1, r);
    tree[root] = 0;
}

void update(int x, int add, int root, int l, int r) {
    if(l == r) {
        tree[root] += add;
        return ;
    }
    MID;
    if(mid < x) {
        update(x, add, root*2+1, mid+1, r);
    } else {
        update(x, add, root*2, l, mid);
    }
    tree[root] = tree[root*2] + tree[root*2+1];
}
int query(int ql, int qr, int root, int l, int r) {
    if(ql <= l and qr >= r) {
        return tree[root];
    }
    MID;
    int res = 0;
    if(qr > mid) {
        res += query(ql, qr, root*2+1, mid+1, r);
    }
    if(ql <= mid) {
        res += query(ql, qr, root*2, l, mid);
    }
    return res;
}

int main() {
    int n, q, t, x1, y1, x2, y2;
    scanint(t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d:\n", tc);
        scanint(n), scanint(q);
        map<int, int> cmp;
        for(int i = 0; i < n; i++) {
            scanint(x1), scanint(y1);
            points[i] = {x1, y1};
            cmp[y1] = 0;
        }
        for(int i = 0; i < q; i++) {
            scanint(x1), scanint(y1), scanint(x2), scanint(y2);
            events[i*2] = {x1 - 1, y1, y2, 1, i};
            events[i*2+1] = {x2, y1, y2, -1, i};
            cmp[y1] = cmp[y2] = 0;
        }
        int cnt = 0;
        for(map<int, int>::iterator it = cmp.begin(); it != cmp.end(); it++) {
            it->second = ++cnt;
        }
        build_tree(1, 1, cnt);
        for(int i = 0; i < n; i++)  points[i].y = cmp[points[i].y];
        for(int i = 0; i < 2*q; i++)
            events[i].y1 = cmp[events[i].y1], events[i].y2 = cmp[events[i].y2];
        sort(points, points + n);
        sort(events, events + 2*q);
        int ptr = 0;
        for(int i = 0; i < 2*q; i++) {
            while(ptr < n and points[ptr].x <= events[i].x) {
                update(points[ptr].y, 1, 1, 1, cnt);
                ptr++;
            }
            if(events[i].type == 1) {
                answer[events[i].idx] -= query(events[i].y1, events[i].y2, 1, 1, cnt);
            } else {
                answer[events[i].idx] += query(events[i].y1, events[i].y2, 1, 1, cnt);
            }
        }
        for(int i = 0; i < q; i++) {
            printf("%d\n", answer[i]);
            answer[i] = 0;
        }
    }
    return 0;
}
