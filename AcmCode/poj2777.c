#include <stdio.h>
#include <string.h>

#define MAX_LENTH 100006
#define MAX_COLOR 31

struct Segment {
    int left;
    int right;
    int color;
};

struct Segment segment[MAX_LENTH * 4];
int vis[MAX_COLOR], ans;
int lenth, color_number, operation_number;

void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].color = 0;
    if (left == right) {
         return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void update(int order, int left, int right, int color) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left >= left && segment[order].right <= right) {
        segment[order].color = color;
        return ;
    }
    if (segment[order].color) {
        segment[order * 2 + 1].color = segment[order * 2].color = segment[order].color;
        segment[order].color = 0;
    }
    if (right <= mid) {
        update(order * 2 , left, right, color);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, color);
    }
    else {
        update(order * 2, left, mid, color);
        update(order * 2 + 1, mid + 1, right, color);
    }
}

int query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left >= left && segment[order].right <= right && segment[order].color) {
        if (!vis[segment[order].color]) {
            ans++;
            vis[segment[order].color] = 1;
        }
        return ;
    }
    if (segment[order].color) {
        segment[order * 2 + 1].color = segment[order * 2].color = segment[order].color;
        segment[order].color = 0;
    }
    if (right <= mid) {
        query(order * 2 , left, right);
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

    int i, start_point, end_point, color, swap;
    char operation[2];
    while (scanf("%d%d%d", &lenth, &color_number, &operation_number) != EOF) {
        build(1, 1, lenth);
        update(1, 1, lenth, 1);
        for (i = 0; i < operation_number; i++) {
            scanf("%s", operation);
            if (operation[0] == 'C') {
                scanf("%d%d%d", &start_point, &end_point, &color);
                if (start_point > end_point) {
                    swap = start_point;
                    start_point = end_point;
                    end_point = swap;
                }
                update(1, start_point, end_point, color);
            }
            else {
                scanf("%d%d", &start_point, &end_point);
                if (start_point > end_point) {
                    swap = start_point;
                    start_point = end_point;
                    end_point = swap;
                }
                ans = 0;
                memset(vis, 0, sizeof(vis));
                query(1, start_point, end_point);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
