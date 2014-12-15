#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>

using namespace std;


#define MAX_NUMBER 10005


struct Segment {
    int left;
    int right;
    int cover;
    double length_one;
    double length_more;
};

struct Point {
    double x;
    double y_1;
    double y_2;
    int flag;
};

struct Segment segment[MAX_NUMBER * 4];
struct Point point[MAX_NUMBER * 2];
double hash_number[MAX_NUMBER * 2];
int point_number, coor_number;

bool cmp(struct Point a, struct Point b) {
    return a.x < b.x;
}

void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].cover = 0;
    segment[order].length_one = segment[order].length_more = 0;
    if (left + 1 == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid , right);
}

void pushUp(int order) {
    if (segment[order].cover >= 2) {
        segment[order].length_more = hash_number[segment[order].right] - hash_number[segment[order].left];
        segment[order].length_one = 0;
    }
    else if (segment[order].cover == 1) {
        if (segment[order].left + 1 == segment[order].right) {
            segment[order].length_more = 0;
        }
        else {
            segment[order].length_more = segment[order * 2].length_more + segment[order * 2 + 1].length_more + segment[order * 2].length_one + segment[order * 2 + 1].length_one;
        }
    segment[order].length_one = hash_number[segment[order].right] - hash_number[segment[order].left] - segment[order].length_more;        
    }
    else {
        if (segment[order].left + 1 == segment[order].right) {
            segment[order].length_more = segment[order].length_one = 0;
        }
        else {
            segment[order].length_more = segment[order * 2].length_more + segment[order * 2 + 1].length_more;
            segment[order].length_one = segment[order * 2].length_one + segment[order * 2 + 1].length_one;
        }
    }
}

void insert(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (segment[order].left >= left && segment[order].right <= right) {
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
        insert(order * 2 + 1, mid , right);
    }
    pushUp(order);
}

void del(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (segment[order].left >= left && segment[order].right <= right) {
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


int searchIndex(double number) {
    int low, high, mid;
    low = 1;
    high = coor_number;
    while (low <= high) {
        mid = (low + high) >> 1;
        if (fabs(hash_number[mid] - number) <= 1e-6) {
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

void init() {
    int i, m;
    for (m = 1, i = 2; i <= point_number * 2; i++) {
        if (hash_number[i - 1] != hash_number[i]) {
            m++;
        }
        hash_number[m] = hash_number[i];
    }
    coor_number = m;
}


int main() {

    int test_case, i, left, right;
    double total_area, pre_length, x_1, y_1, x_2, y_2;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &point_number);
        total_area = 0;
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
        sort(hash_number, hash_number + point_number * 2 + 1);
        sort(point + 1, point + 1 + point_number * 2, cmp);
        init();
        build(1, 1, coor_number);
        left = searchIndex(point[1].y_1);
        right = searchIndex(point[1].y_2);
        insert(1, left, right);
        pre_length = segment[1].length_more;
        for (i = 2; i <= point_number * 2; i++) {
            left = searchIndex(point[i].y_1);
            right = searchIndex(point[i].y_2);
            if (point[i].flag) {
                del(1, left, right);
            }
            else {
                insert(1, left, right);
            }
            total_area += pre_length * (point[i].x - point[i - 1].x);
            pre_length = segment[1].length_more;
        }
        printf("%.2lf\n", total_area);
    }
    return 0;
}

