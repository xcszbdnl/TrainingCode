#include <stdio.h>

#define MAX_NUMBER 1000001
#define max(a, b) ((a) > (b))? (a) : (b)
#define min(a, b) ((a) > (b))? (b) : (a)

struct Segment {
    int left, right;
    int max_number, min_number;
};

struct Segment segment[5 * MAX_NUMBER];
int ans[2][MAX_NUMBER];
int numbers[MAX_NUMBER];
int size, min_ans, max_ans;

void create(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        segment[order].max_number = segment[order].min_number = numbers[left];
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
        max_ans = max(segment[order].max_number, max_ans);
        min_ans = min(segment[order].min_number, min_ans);
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

    int i, lenth;
    scanf("%d%d", &size, &lenth);
    for (i = 1; i <= size; i++) {
        scanf("%d", &numbers[i]);
    }
    create(1, 1, size);
    for (i = 1; i + lenth - 1<= size; i++) {
        max_ans = min_ans = numbers[i];
        search(1, i, i + lenth - 1);
        ans[0][i] = max_ans;
        ans[1][i] = min_ans;
    }
    for (i = 1; i + lenth - 1 <= size; i++) {
        if (i == 1) {
            printf("%d", ans[1][i]);
        }
        else {
            printf(" %d", ans[1][i]);
        }
    }
    printf("\n");    
    for (i = 1; i + lenth - 1 <= size; i++) {
        if (i == 1) {
            printf("%d", ans[0][i]);
        }
        else {
            printf(" %d", ans[0][i]);
        }
    }
    printf("\n");
}
