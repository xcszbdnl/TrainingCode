#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int maxn = 100007;

struct Seg {
    int left, right, val, lazy;
};

struct Query {
    int l, r, val;
};


struct Seg seg[maxn * 4];
struct Query q[maxn];
int n, m;

void build(int order, int left, int right) {
    seg[order].left = left;
    seg[order].right = right;
    seg[order].val = 0;
    seg[order].lazy = 0;
    int mid = (left + right) >> 1;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void pushUp(int order) {
    seg[order].val = seg[order * 2].val & seg[order * 2 + 1].val;
}

void pushDown(int order) {
    if (seg[order].lazy) {
        seg[order * 2].val |= seg[order].lazy;
        seg[order * 2 + 1].val |= seg[order].lazy;
        seg[order * 2].lazy |= seg[order].lazy;
        seg[order * 2 + 1].lazy |= seg[order].lazy;
        seg[order].lazy = 0;
    }
}


void update(int order, int left, int right, int val) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        seg[order].val |= val;
        seg[order].lazy |= val;
        return ;
    }
    pushDown(order);
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
    pushUp(order);
}

int query(int order, int left, int right) {
    int mid = (seg[order].left + seg[order].right) >> 1;
    if (left <= seg[order].left && right >= seg[order].right) {
        return seg[order].val;
    }
    pushDown(order);
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        int left_ans = query(order * 2, left, mid);
        int right_ans = query(order * 2 + 1, mid + 1, right);
        return left_ans & right_ans;
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &q[i].l, &q[i].r, &q[i].val);
        update(1, q[i].l, q[i].r, q[i].val);
    }
    int flag = 0;
    for (int i = 1; i <= m; i++) {
        int temp = query(1, q[i].l, q[i].r);
        if (temp != q[i].val) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        printf("NO\n");
        return 0;
    }
    else {
        printf("YES\n");
        for (int i = 1; i <= n; i++) {
            printf("%d ",query(1, i, i));
        }
    }
    return 0;
}
