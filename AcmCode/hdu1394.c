#include <stdio.h>

#define MAX_NUMBER 5001
#define min(a, b) ((a) > (b)) ? (b) : (a)

struct Segment {
    int left, right;
    int sum;
};

struct Segment segment[4 * MAX_NUMBER];
int numbers;
int array[MAX_NUMBER];

void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        segment[order].sum = 0;
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    segment[order].sum = segment[order * 2].sum + segment[order * 2 + 1].sum;
}

void update(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (segment[order].left == left && segment[order].right == right) {
        segment[order].sum = 1;
        return ;
    }
    if (right <= mid) {
        update(order * 2, left, right);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right);
    }
    else {
        update(order * 2, left, mid);
        update(order * 2 + 1, mid + 1, right);
    }
    segment[order].sum = segment[order * 2].sum + segment[order * 2 + 1].sum;
}

int query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (segment[order].left == left && segment[order].right == right) {
        return segment[order].sum;
    }
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        return query(order * 2, left, mid) + query(order * 2 + 1, mid + 1, right);
    }
}


int main() {

    int i, sums, min_ans;
    while (scanf("%d", &numbers) != EOF) {
        sums = 0;
        build(1, 0, numbers - 1);
        for (i = 0; i < numbers; i++) {
            scanf("%d", &array[i]);
            sums += query(1, array[i], numbers - 1);
            update(1, array[i], array[i]);
        }
        min_ans = sums;
        for (i = 0; i < numbers; i++) {
            sums = sums + (numbers - 1 - array[i]) - (array[i]);
            min_ans = min(sums, min_ans);
        }
        printf("%d\n", min_ans);
    }
}
