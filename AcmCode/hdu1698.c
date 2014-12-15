#include <stdio.h>


#define MAX_NUMBER 100005

struct Segment {
    int left;
    int right;
    int kind;
    int sums;
};

struct Segment segment[MAX_NUMBER * 4];
int number_of_sticks;

void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].kind = 1;
    if (left == right) {
        segment[order].sums = (right - left + 1);
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    segment[order].sums = segment[order * 2].sums + segment[order *  2 + 1].sums;
}

void update(int order, int left, int right, int kind) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left >= left && segment[order].right <= right) {
        segment[order].kind = kind;
        segment[order].sums = (segment[order].right - segment[order].left + 1) * kind;
        return ;
    }
    if (segment[order].kind != 0) {
        segment[order * 2].kind = segment[order * 2 + 1].kind = segment[order].kind;
        segment[order * 2].sums = (mid - segment[order * 2].left + 1) * segment[order].kind;
        segment[order * 2 + 1].sums = (segment[order * 2 + 1].right - mid) * segment[order].kind;
        segment[order].kind = 0;
    }
    if (right <= mid) {
        update(order * 2, left, right, kind);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, kind);
    }
    else {
        update(order * 2, left, mid, kind);
        update(order * 2 + 1, mid + 1, right, kind);
    }
    segment[order].sums = segment[order * 2].sums + segment[order * 2 + 1].sums;
}

int main() {

    int test_case;
    int i, start_point, end_point, kind, operation_number;
    int case_number = 1;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &number_of_sticks);
        scanf("%d", &operation_number);
        build(1, 1, number_of_sticks);
        for (i = 0; i < operation_number; i++) {
            scanf("%d%d%d", &start_point, &end_point, &kind);
            update(1, start_point, end_point, kind);
        }
        printf("Case %d: The total value of the hook is %d.\n", case_number, segment[1].sums);
        case_number++;
    }
    return 0;
}
