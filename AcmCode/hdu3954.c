#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 10005
#define MAX_LEVEL 12
#define max(a,b) ((a) > (b)) ? (a) : (b)

struct Segment {
    int left;
    int right;
    int max_exp[MAX_LEVEL];
    int add[MAX_LEVEL];
};


struct Segment segment[MAX_NUMBER * 4];
int need_exp[MAX_LEVEL];
int max_level, hero_number, operation_number;

void pushUp(int order) {
    int i;
    for (i = 1; i <= max_level; i++) {
        segment[order].max_exp[i] = max(segment[order * 2].max_exp[i], segment[order * 2 + 1].max_exp[i]);
    }
}

void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    int i;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].max_exp[1] = 0;
    segment[order].add[1] = 0;
    for (i = 2; i <= max_level; i++) {
        segment[order].max_exp[i] = -1;
        segment[order].add[i] = 0;
    }
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    pushUp(order);
}

void pushDown(int order) {
    int i;
    for (i = 1; i <= max_level; i++) {
        if (segment[order].add[i]) {
            if (segment[order * 2].max_exp[i] != -1) {
                segment[order * 2].add[i] += segment[order].add[i];
                segment[order * 2].max_exp[i] += segment[order].add[i];
            }
            if (segment[order * 2 + 1].max_exp[i] != -1) {
                segment[order * 2 + 1].add[i] += segment[order].add[i];
                segment[order * 2 + 1].max_exp[i] += segment[order].add[i];
            }
            segment[order].add[i] = 0;
        }
    }
}

void levelUp(int order, int level) {
    if (segment[order].left == segment[order].right) {
        segment[order].max_exp[level + 1] = segment[order].max_exp[level];
        segment[order].max_exp[level] = -1;
        return ;
    }
    pushDown(order);
    if (segment[order * 2].max_exp[level] > segment[order * 2 + 1].max_exp[level]) {
        levelUp(order * 2, level);
    }
    else {
        levelUp(order * 2 + 1, level);
    }
    pushUp(order);
}

void update(int order, int left, int right, int exp) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    int i;
    if (segment[order].left >= left && segment[order].right <= right) {
        for (i = 1; i <= max_level; i++) {
            if (segment[order].max_exp[i] != -1) {
                segment[order].max_exp[i] += i * exp;
                segment[order].add[i] += i * exp;
            }
        }
        for (i = 1; i < max_level; i++) {
            while (segment[order].max_exp[i] >= need_exp[i + 1]) {
                levelUp(order, i);
            }
        }
        return ;
    }
    pushDown(order);
    if (right <= mid) {
        update(order * 2, left, right, exp);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right, exp);
    }
    else {
        update(order * 2, left, mid, exp);
        update(order * 2 + 1, mid + 1, right, exp);
    }
    pushUp(order);
}

int query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    int l_ans, r_ans, i;
    if (segment[order].left >= left && segment[order].right <= right) {
        for (i = max_level; i >= 1; i--) {
            if (segment[order].max_exp[i] != -1) {
                return segment[order].max_exp[i];
            }
        }
    }
    pushDown(order);
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        l_ans = query(order * 2, left, mid);
        r_ans = query(order * 2 + 1, mid + 1, right);
        return max(l_ans, r_ans);
    }
}

int main() {

    int test_case, i, left, right, exp, ans, case_number = 1;
    char operation[10];
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d%d", &hero_number, &max_level, &operation_number);
        for (i = 2; i <= max_level; i++) {
            scanf("%d", &need_exp[i]);
        }
        build(1, 1, hero_number);
        printf("Case %d:\n", case_number);
        for (i = 0; i < operation_number; i++) {
            scanf("%s", operation);
            if (operation[0] == 'W') {
                scanf("%d%d%d", &left, &right, &exp);
                update(1, left, right, exp);
            }
            else {
                scanf("%d%d", &left, &right);
                ans = query(1, left, right);
                printf("%d\n", ans);
            }
        }
        case_number++;
        printf("\n");
    }
    return 0;
}
