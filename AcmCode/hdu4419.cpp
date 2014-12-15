#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

#define COLOR_NUMBER 8
#define MAX_NUMBER 10020

using namespace std;


struct Segment {
    int left;
    int right;
    int cover[4];
    long long length[COLOR_NUMBER];
};

struct Point {
    long long x;
    long long y_1;
    long long y_2;
    int color;
    int flag;
};

struct Segment segment[MAX_NUMBER * 6];
struct Point point[MAX_NUMBER * 3];
long long hash_number[MAX_NUMBER * 3];
int coor_number, rect_number;

bool cmp(struct Point a, struct Point b) {
    return a.x < b.x;
}

void build(int order, int left, int right) {
    int i;
    int mid = (left + right) >> 1;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].length[0] = hash_number[right] - hash_number[left];
    for (i = 1; i <= 7; i++) {
        segment[order].length[i] = 0;
    }
    for (i = 1; i <= 3; i++) {
        segment[order].cover[i] = 0;
    }
    if (left == right - 1) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid, right);
}


void pushUp(int order) {
    int final_color = 0;
    int i;
    for (i = 0; i < 3; i++) {
        if (segment[order].cover[i]) {
            final_color |= (1 << i);
        }
    }
    memset(segment[order].length, 0, sizeof(segment[order].length));        
    if (segment[order].right == segment[order].left + 1) {
        segment[order].length[final_color] = hash_number[segment[order].right] - hash_number[segment[order].left];
    }
    else {
        for (i = 0; i <= 7; i++) {
            segment[order].length[i | final_color] += segment[order * 2].length[i] + segment[order * 2 + 1].length[i];
        }
    }
}

void insert(int order, int left, int right, int color) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (segment[order].left >= left && segment[order].right <= right) {
        segment[order].cover[color]++;
    }
    else if (right <= mid) {
        insert(order * 2, left, right, color);
    }
    else if (left >= mid) {
        insert(order * 2 + 1, left, right, color);
    }
    else {
        insert(order * 2, left, mid, color);
        insert(order * 2 + 1, mid, right, color);
    }
    pushUp(order);
}

void del(int order, int left, int right, int color) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (segment[order].left >= left && segment[order].right <= right) {
        segment[order].cover[color]--;
    }
    else if (right <= mid) {
        del(order * 2, left, right, color);
    }
    else if (left >= mid) {
        del(order * 2 + 1, left, right, color);
    }
    else {
        del(order * 2, left, mid, color);
        del(order * 2 + 1, mid, right, color);
    }
    pushUp(order);
}

int colorNumber(char color) {
    if (color == 'R') {
        return 0;
    }
    else if (color == 'G'){
        return 1;
    }
    else {
        return 2;
    }
}

void init() {
    int i,m;
    for (i = 2, m = 1; i <= rect_number * 2; i++) {
        if (hash_number[i - 1] != hash_number[i]) {
            m++;
        }
        hash_number[m] = hash_number[i];
    }
    coor_number = m;
}

int searchIndex(long long number) {
    int low, high, mid;
    low = 1;
    high = coor_number;
    while (low <= high) {
        mid = (low + high) >> 1;
        if (hash_number[mid] == number) {
            return mid;
        }
        else if (hash_number[mid] > number) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
}

int main() {

    int test_case, i, j, x_1, y_1, x_2, y_2, point_color, left, right, case_number = 1;
    long long ans[10];
    char color[10];
    scanf("%d", &test_case);
    while (test_case--) {
        memset(ans, 0, sizeof(ans));
        scanf("%d", &rect_number);
        for (i = 1; i <= rect_number * 2; i += 2) {
            scanf("%s%d%d%d%d", color, &x_1, &y_1, &x_2, &y_2);
            point_color = colorNumber(color[0]);
            point[i].x = x_1;
            point[i].y_1 = y_1;
            point[i].y_2 = y_2;
            point[i].flag = 0;
            point[i].color = point_color;
            point[i + 1].x = x_2;
            point[i + 1].y_1 = y_1;
            point[i + 1].y_2 = y_2;
            point[i + 1].flag = 1;
            point[i + 1].color = point_color;
            hash_number[i] = y_1;
            hash_number[i + 1] = y_2;
        }
        sort(point + 1, point + 1 + rect_number * 2, cmp);
        sort(hash_number + 1, hash_number + 1 + rect_number * 2);
        init();
        build(1, 1, coor_number);
        for (i = 1; i < rect_number * 2; i++) {
            left = searchIndex(point[i].y_1);
            right = searchIndex(point[i].y_2);
            if (point[i].flag) {
                del(1, left, right, point[i].color);
            }
            else {
                insert(1, left, right, point[i].color);
            }
            for (j = 1; j <= 7; j++) {
                ans[j] += segment[1].length[j] * (point[i + 1].x - point[i].x);
            }
        }
        printf("Case %d:\n", case_number);
        for (i = 1; i <= 7; i++) {
            if (i == 3) {
                printf("%I64d\n", ans[4]);
            }
            else if (i == 4) {
                printf("%I64d\n", ans[3]);
            }
            else {
                printf("%I64d\n", ans[i]);
            }
        }
        case_number++;
    }
}
