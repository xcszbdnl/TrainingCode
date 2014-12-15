#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 50001

struct Segment {
    int left, right;
    int sum;
};

struct Segment segment[MAX_NUMBER * 5];
int original_number[MAX_NUMBER];


void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        segment[order].sum = original_number[left];
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    segment[order].sum = segment[order * 2].sum + segment[order * 2 + 1].sum;
}

void update(int order, int left, int right, int sum) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left == left && segment[order].right == right) {
        segment[order].sum += sum;
        return ;
    }
    if (right <= mid) {
        update(order * 2, left, right, sum);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, sum);
    }
    else {
        update(order * 2, left, mid, sum);
        update(order * 2 + 1, mid + 1, right, sum);
    }
    segment[order].sum = segment[order * 2].sum + segment[order * 2 + 1].sum;
}

int query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
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

    int test_case, number, instruct_number, sums, case_number = 1;
    int i, instruct_1, instruct_2;
    char instruct[100];
    scanf("%d", &test_case);
    while (test_case--) {
        printf("Case %d:\n", case_number);
        scanf("%d", &number);
        memset(segment, 0, sizeof(segment));
        for (i = 1; i <= number; i++) {
            scanf("%d", &original_number[i]);
        }
        build(1,1,number);
        while (scanf("%s", instruct) != EOF) {
            if (instruct[0] == 'E') {
                break;
            }
            scanf("%d%d", &instruct_1, &instruct_2);
            if (instruct[0] == 'A') {
                update(1, instruct_1, instruct_1, instruct_2);
            }
            else if (instruct[0] == 'S') {
                update(1, instruct_1, instruct_1, -instruct_2);
            }
            else {
                sums = query(1, instruct_1, instruct_2);
                printf("%d\n", sums);
            }
            
        }
        case_number++;
    }
    return 0;
}
