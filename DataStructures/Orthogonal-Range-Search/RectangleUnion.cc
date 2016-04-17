/* Author: Ankit Sultana
 * Problem id: 1120
 * * * * * * * * * */
#ifdef __APPLE__
    #include <iostream>
#endif
#include <stdio.h>
#include <algorithm>
#define LL long long
#define MID int mid = (((right_lmt - left_lmt)/2) + left_lmt)
#define INF 1<<30
#define MAXN 30010

using namespace std;
int segsize = 0, n;
struct segnode {
    int open, l, r;
    LL length;
}segtree[50*MAXN];

struct event {
    int type, x, y1, y2;
    bool operator<(const event &other) const {
        return x == other.x ? type > other.type: x < other.x;
    }
}events[MAXN*2];

void segupdate(int ql, int qr, int type, int &segroot, int left_lmt = 0, int right_lmt = INF) {
    if(segroot == 0) {
        segroot = ++segsize;
        segtree[segroot] = {0, 0, 0, 0};
    }
    if(ql <= left_lmt and qr >= right_lmt) {
        segtree[segroot].open += type;
        if(segtree[segroot].open == 0) {
            segtree[segroot].length = segtree[segtree[segroot].l].length + segtree[segtree[segroot].r].length;
        } else if(segtree[segroot].open == 1) {
            segtree[segroot].length = (LL)(right_lmt - left_lmt + 1);
        }
        return ;
    }
    MID;
    if(mid < qr) {
        segupdate(ql, qr, type, segtree[segroot].r, mid+1, right_lmt);
    }
    if(ql <= mid) {
        segupdate(ql, qr, type, segtree[segroot].l, left_lmt, mid);
    }
    if(segtree[segroot].open == 0)
        segtree[segroot].length = segtree[segtree[segroot].l].length + segtree[segtree[segroot].r].length;
}

int main() {
    int t, x1, y1, x2, y2;
    scanf("%d", &t);
    for(int tc = 1; tc <= t; tc++) {
        printf("Case %d: ", tc);
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            events[i*2] = {1, x1, y1, y2};
            events[i*2+1] = {-1, x2, y1, y2};
        }
        segsize = 0;
        sort(events, events + 2*n);
        int p = -1, root = 0;
        segupdate(events[0].y1, events[0].y2, 1, root);
        LL answer = 0;
        p = events[0].x;
        for(int i = 1; i < 2*n; i++) {
            LL temp = (LL)(events[i].x - p) * (segtree[root].length - 1);
            answer += max(0ll, temp);
            segupdate(events[i].y1, events[i].y2, events[i].type, root);
            p = events[i].x;
        }
        printf("%lld\n", answer);
    }
    return 0;
}
