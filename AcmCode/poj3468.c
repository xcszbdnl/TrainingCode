#include <stdio.h>


#define MAX_NUMBER 100006


struct Segment {
    int left;
    int right;
    long long sums;
    long long store;
};


struct Segment segment[MAX_NUMBER * 4];
long long values[MAX_NUMBER];


void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].store = 0;
    if (left == right) {
        segment[order].sums = values[left];
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    segment[order].sums = segment[order * 2].sums + segment[order * 2 + 1].sums;
}

void update(int order, int left, int right, long long add_values) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left >= left && segment[order].right <= right) {
        segment[order].store += add_values;
        segment[order].sums += (segment[order].right - segment[order].left + 1) * add_values;
        return ;
    }
    if (segment[order].store != 0) {
        segment[order * 2].store += segment[order].store;
        segment[order * 2 + 1].store += segment[order].store;
        segment[order * 2].sums += (mid - segment[order * 2].left + 1) * segment[order].store;
        segment[order * 2 + 1].sums += (segment[order * 2 + 1].right - mid) * segment[order].store;
        segment[order].store = 0;
    }
    if (right <= mid) {
        update(order * 2, left, right, add_values);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, add_values);
    }
    else {
        update(order * 2, left, mid, add_values);
        update(order * 2 + 1, mid + 1, right, add_values);
    }
    segment[order].sums = segment[order * 2].sums + segment[order * 2 + 1].sums;
}

long long query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left >= left && segment[order].right <= right) {
        return segment[order].sums;
    }
    if (segment[order].store != 0) {
        segment[order * 2].store += segment[order].store;
        segment[order * 2 + 1].store += segment[order].store;
        segment[order * 2].sums += (mid - segment[order * 2 ].left + 1) * segment[order].store;
        segment[order * 2 + 1].sums += (segment[order * 2 + 1].right - mid) * segment[order].store;
        segment[order].store = 0;
    }
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid){
        return query(order * 2 + 1, left, right);
    }
    else {
        return query(order * 2, left, mid) + query(order * 2 + 1, mid + 1, right);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int numbers, operation_number, start_point, end_point, add_values;
    int i;
    long long sums;
    char operation[10];
    scanf("%d%d", &numbers, &operation_number);
    for (i = 1; i <= numbers; i++) {
        scanf("%lld", &values[i]);
    }
    build(1, 1, numbers);
    for (i = 1; i <= operation_number; i++) {
        scanf("%s", operation);
        if (operation[0] == 'Q') {
            scanf("%d%d", &start_point, &end_point);
            sums = query(1, start_point, end_point);
            printf("%lld\n", sums);
        }
        else {
            scanf("%d%d%d", &start_point, &end_point, &add_values);
            update(1, start_point, end_point, add_values);
        }
    }
    return 0;
}
