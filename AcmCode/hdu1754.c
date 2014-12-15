#include <stdio.h>

#define MAX_NUMBER 200002
#define max(a,b) ((a) > (b)) ? (a) : (b)

struct Segment {
    int left, right;
    int max_number;
};

struct Segment segment[MAX_NUMBER * 4];


void create(int order, int left, int right) {
    int mid = (left + right) >> 1;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        scanf("%d", &segment[order].max_number);
        return ;
    }
    create(order * 2, left, mid);
    create(order * 2 + 1, mid + 1, right);
    segment[order].max_number = max(segment[order * 2].max_number, segment[order * 2 + 1].max_number);
}

void update(int order, int left, int right, int update_number) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left == left && segment[order].right == right) {
        segment[order].max_number = update_number;
        return ;
    }
    if (right <= mid) {
        update(order * 2, left, right, update_number);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, update_number);
    }
    else {
        update(order * 2 , left, mid, update_number);
        update(order * 2 + 1, mid + 1, right, update_number);
    }
    segment[order].max_number = max(segment[order * 2].max_number, segment[order * 2 + 1].max_number);
}

int query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    int left_max, right_max;
    if (segment[order].left == left && segment[order].right == right) {
        return segment[order].max_number;
    }
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        left_max = query(order * 2, left, mid);
        right_max = query(order * 2 + 1, mid + 1, right);
        return max(left_max, right_max);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int student_number, operation_number, op_1, op_2;
    char operation[6];
    int i, max_number;
    while (scanf("%d%d", &student_number, &operation_number) != EOF) {
        create(1, 1, student_number);
        for (i = 1; i <= operation_number; i++) {
            scanf("%s", operation);
            scanf("%d%d", &op_1, &op_2);
            if (operation[0] == 'Q') {
                max_number = query(1, op_1, op_2);
                printf("%d\n", max_number);
            }
            else {
                update(1, op_1, op_1, op_2);
            }
        }
    }
    return 0;
}
