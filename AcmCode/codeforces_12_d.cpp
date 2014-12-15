#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <set>
#include <stack>
using namespace std;

const int maxn = 500007;
struct P {
    int b, i, r;
};

bool cmp(struct P a, struct P b) {
    if (a.b == b.b) {
        if (a.i == b.i) {
            return a.r < b.r;
        }
        return a.i < b.i;
    }
    return a.b < b.b;
}


int n, ans;
int x[maxn];
struct P p[maxn];
stack<struct P> sta;
struct Seg {
    int left, right, max_val, max_order;
};

struct Seg seg[maxn * 4];
void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    seg[order].left = left;
    seg[order].right = right;
    seg[order].max_val = 0;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void update(int order, int left, int right, int val) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        seg[order].max_val = max(seg[order].max_val, val);
        return ;
    }
    if (right <= mid) {
        update(order * 2, left, right, val);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, val);
    }
    else {
        update(order * 2, left, mid, val);
        update(order * 2 + 1, mid + 1, right, val);
    }
    seg[order].max_val = max(seg[order * 2].max_val, seg[order * 2 + 1].max_val);
}

int query(int order, int left, int right) {
    if (left > right) {
        return 0;
    }
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        return seg[order].max_val;
    }
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        return max(query(order * 2, left, mid), query(order * 2 + 1, mid + 1, right));
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i].b);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i].i);
        x[i] = p[i].i;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i].r);
    }
    ans = 0;
    sort(p + 1, p + 1 + n, cmp);
    sort(x + 1, x + 1 + n);
    int tot = unique(x + 1, x + 1 + n) - x - 1;
    for (int i = 1; i <= n; i++) {
        p[i].i = lower_bound(x + 1, x + 1 + tot, p[i].i) - x;
    }
    build(1, 1, tot);
    p[0].r = -1;
    for (int i = n; i >= 1; i--) {
        if (p[i].b != p[i + 1].b) {
            while (!sta.empty()) {
                struct P cnt = sta.top();
                update(1, cnt.i, cnt.i,  cnt.r);
                sta.pop();
            }
        }
        int val = query(1, p[i].i + 1, tot);
        if (val > p[i].r) {
            ans++;
        }
        sta.push(p[i]);
    }
    printf("%d\n", ans);
    return 0;
}
