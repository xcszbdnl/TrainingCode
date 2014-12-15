#include <iostream>
#include <string.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;


#define MAX_NUMBER 300

struct Segment {
    int left;
    int right;
    int cover;
    double lenth;
};

struct Point {
    double x;
    double y_1;
    double y_2;
    int flag;
};

struct Segment segment[MAX_NUMBER * 4];
struct Point point[MAX_NUMBER];
double hash_number[MAX_NUMBER];
int point_number, coor_number;

void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].lenth = 0.0;
    segment[order].cover = 0;
    if (left == right - 1) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid, right);
}

bool cmp(struct Point a, struct Point b) {
    return a.x < b.x;
}

void pushUp(int order) {
    if (segment[order].cover) {
        segment[order].lenth = hash_number[segment[order].right] - hash_number[segment[order].left];
    }
    else {
        if (segment[order].left + 1 == segment[order].right) {
            segment[order].lenth = 0;
        }
        else {
            segment[order].lenth = segment[order * 2].lenth + segment[order * 2 + 1].lenth;
        }
    }
}

void insert(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (left <= segment[order].left && right >= segment[order].right) {
        segment[order].cover++;
    }
    else if (right <= mid) {
        insert(order * 2, left, right);
    }
    else if (left >= mid) {
        insert(order * 2 + 1, left, right);
    }
    else {
        insert(order * 2, left, mid);
        insert(order * 2 + 1, mid, right);
    }
    pushUp(order);
}

void del(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (left <= segment[order].left && right >= segment[order].right) {
        segment[order].cover--;
    }
    else if (right <= mid) {
        del(order * 2, left, right);
    }
    else if (left >= mid) {
        del(order * 2 + 1, left, right);
    }
    else {
        del(order * 2, left, mid);
        del(order * 2 + 1, mid, right);
    }
    pushUp(order);
}

void init() {
    int i, m;
    m = 1;
    for (i = 2; i <= point_number * 2; i++) {
        if (hash_number[i - 1] != hash_number[i]) {
            m++;
        }
        hash_number[m] = hash_number[i];
    }
    coor_number = m;
}

int searchIndex(double number) {
    int high, low, mid;
    high = coor_number;
    low = 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (fabs(hash_number[mid] - number) <= 1e-6) {
            return mid;
        }
        else if (hash_number[mid] > number){
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
}

int main() {

    int test_case, i, j, left, right, pre_lines;
    double x_1, x_2, y_1, y_2, total_area, pre_lenth;
    test_case = 1;
    while (scanf("%d", &point_number) != EOF) {
        if (!point_number) {
            break;
        }
        for (i = 1; i <= point_number * 2; i += 2) {
            scanf("%lf%lf%lf%lf", &x_1, &y_1, &x_2, &y_2);
            point[i].x = x_1;
            point[i].y_1 = y_1;
            point[i].y_2 = y_2;
            point[i].flag = 0;
            point[i + 1].x = x_2;
            point[i + 1].y_1 = y_1;
            point[i + 1].y_2 = y_2;
            point[i + 1].flag = 1;
            hash_number[i] = y_1;
            hash_number[i + 1] = y_2;
        }
        sort(hash_number + 1, hash_number + point_number * 2 + 1);
        sort(point + 1, point + point_number * 2 + 1, cmp);
        init();
        build(1, 1, coor_number);
        left = searchIndex(point[1].y_1);
        right = searchIndex(point[1].y_2);
        insert(1, left, right);
        total_area = 0;
        pre_lenth = segment[1].lenth;
        for (i = 2; i <= point_number * 2; i++) {
            left = searchIndex(point[i].y_1);
            right = searchIndex(point[i].y_2);
            if (!point[i].flag) {
                insert(1, left, right);
            }
            else {
                del(1, left, right);
            }
            total_area += pre_lenth * (point[i].x - point[i - 1].x);
            pre_lenth = segment[1].lenth;
        }
        printf("Test case #%d\n", test_case);
        printf("Total explored area: %.2f\n", total_area);
        printf("\n");
        test_case++;
    }
}
