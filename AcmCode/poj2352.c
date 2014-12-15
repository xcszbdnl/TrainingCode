#include <stdio.h>
#include <string.h>

#define MAX_LENTH 32006

struct Segment {
    int left;
    int right;
    int sums;
};

struct Segment segment[MAX_LENTH * 4];
int level[MAX_LENTH];
int ans;

void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].sums = 0;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void insert(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left == left && right == segment[order].right) {
        segment[order].sums++;
        return ;
    }
    if (right <= mid) {
        insert(order * 2, left, right);
    }
    else if (left > mid) {
        insert(order * 2 + 1, left, right);
    }
    else {
        insert(order * 2, left, mid);
        insert(order * 2 + 1, mid + 1, right);
    }
    segment[order].sums = segment[order * 2].sums + segment[order * 2 + 1].sums;
}

void query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left == left && segment[order].right == right) {
        ans += segment[order].sums;
        return ;
    }
    if (right <= mid) {
        query(order * 2, left, right);
    }
    else if (left > mid) {
        query(order * 2 + 1, left, right);
    }
    else {
        query(order * 2, left, mid);
        query(order * 2 + 1, mid + 1, right);
    }
}

int main() {

    int star_number, i, x, y;
    scanf("%d", &star_number);
    memset(level, 0, sizeof(level));
    build(1, 1, MAX_LENTH);
    for (i = 0; i < star_number; i++) {
        scanf("%d%d", &x, &y);
        ans = 0;
        x += 1;
        query(1, 1, x);
        level[ans]++;
        insert(1, x, x);
    }
    for (i = 0; i < star_number; i++) {
        printf("%d\n", level[i]);
    }
    return 0;
}
