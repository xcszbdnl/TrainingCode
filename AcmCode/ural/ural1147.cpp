#include <cstdio>
#include <cstring>

const int maxn = 10007;

struct Segment {
    int left, right, lazy, color, pre_color;
};



struct Ret ret[maxn];
struct Segment segment[maxn * 4];
int ans[maxn], n, a, b;

void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].lazy = 0;
    segment[order].color = 0;
    segment[order].pre_color = 0;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void pushUp(int order) {
    if (segment[order * 2].color == segment[order * 2 + 1].color) {
        segment[order].color = segment[order * 2].color;
    }
    else{
        segment[order].color = -1;
    }
}

void pushDown(int order) {
    if (segment[order].lazy) {
        segment[order].lazy = 1;
        segment[order * 2].lazy = segment[order * 2 + 1].lazy = 1;
        segment[order * 2].pre_color = segment[order * 2].color;
        segment[order * 2 + 1].pre_color = segment[order * 2 + 1].color;
        segment[order * 2].color = segment[order * 2 + 1].color = segment[order].color;
    }
}

void add(int order, int left, int right, int color) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (left <= segment[order].left && right >= segment[order].right) {
        segment[order].pre_color = segment[order].color;
        segment[order].color = color;
        segment[order].lazy = 1;
        return ;
    }
    pushDown(order);
    if (right <= mid) {
        update(order * 2, left, right, color);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, color);
    }
    else {
        update(order * 2, left, mid, color);
        update(order * 2 + 1, mid + 1, right, color);
    }
    pushUp(order);
}

void del(int order, int left, int right) {
}
void query(int order, int x) {
    if (segment[order].color == 0) {
        return ;
    }
    if (segment[order].color != -1) {
        ans[segment[order].color] += (segment[order].right * segment[order].left + 1) * x;
    }
    else {
        query(order * 2, x);
        query(order * 2 + 1, x);
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 1; i <= n; i++) {

    }
}
