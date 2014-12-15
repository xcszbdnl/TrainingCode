#include <stdio.h>

#define MAX_NUMBER 50010
#define max(a, b) ((a) > (b)) ? (a) : (b)
#define min(a, b) ((a) > (b)) ? (b) : (a)

struct Segment {
    int left, right;
    int max_number, min_number;
};

struct Segment segment[5 * MAX_NUMBER];

int height[MAX_NUMBER];
int pointer, max_ans, min_ans;

void create(int order, int left, int right) {
    int mid;
    mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        segment[order].max_number = segment[order].min_number = height[left];
        return ;
    }
    create(order * 2, left, mid);
    create(order * 2 + 1, mid + 1, right);
    segment[order].max_number = max(segment[order * 2].max_number, segment[order * 2 + 1].max_number);
    segment[order].min_number = min(segment[order * 2].min_number, segment[order * 2 + 1].min_number);
}

void search(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left == left && segment[order].right == right) {
        max_ans = max(max_ans, segment[order].max_number);
        min_ans = min(min_ans, segment[order].min_number);
        return ;
    }
    if (right <= mid) {
        search(order * 2, left, right);
    }
    else if (left > mid) {
        search(order * 2 + 1, left, right);
    }
    else {
        search(order * 2, left, mid);
        search(order * 2 + 1, mid + 1, right);
    }
}

int main() {

    int cows_number, query_number;
    int i, group_left, group_right;
    while (scanf("%d%d", &cows_number, &query_number) != EOF) {
        for (i = 1; i <= cows_number; i++) {
            scanf("%d", &height[i]);
        }
        create(1, 1, cows_number);
        for (i = 1; i <= query_number; i++) {
            scanf("%d%d", &group_left, &group_right);
            max_ans = min_ans = height[group_left];
            search(1, group_left, group_right);
            printf("%d\n", max_ans - min_ans);
        }
    }
    return 0;
}
