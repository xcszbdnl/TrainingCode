#include <iostream>
#include <cmath>
#include <stdio.h>
#include <algorithm>

using namespace std;


#define MAX_NUMBER 10005


struct Segment {
    int left, right;
    int cover_l, cover_r, lenth, lines, cover;
};

struct Coordinate {
    int x;
    int y_1, y_2;
    int flag;
};

struct Segment segment[MAX_NUMBER];
struct Coordinate coordinate[MAX_NUMBER];
int hash_number[MAX_NUMBER], rectangle_number, coor_number;

bool cmp(struct Coordinate a, struct Coordinate b) {
    return a.x < b.x;
}

void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].cover_l = segment[order].cover_r = segment[order].lenth = segment[order].lines = segment[order].cover = 0;
    if (left == right - 1) {
        return ;
    }
    build(order * 2, left , mid);
    build(order * 2 + 1, mid , right);
}

void update(int order) {
    if (segment[order].cover) {
        segment[order].lenth = hash_number[segment[order].right] - hash_number[segment[order].left];
        segment[order].lines = 1;
        segment[order].cover_l = segment[order].cover_r = 1;
    }
    else {
        if (segment[order].right == segment[order].left + 1) {
            segment[order].lenth = 0;
            segment[order].cover_l = segment[order].cover_r = 0;
            segment[order].lines = 0;
        }
        else {
            segment[order].lines = segment[order * 2].lines + segment[order * 2 + 1].lines - segment[order * 2].cover_r * segment[order * 2 + 1].cover_l;
            segment[order].lenth = segment[order * 2].lenth + segment[order * 2 + 1].lenth;
            segment[order].cover_l = segment[order * 2].cover_l;
            segment[order].cover_r = segment[order * 2 + 1].cover_r;
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
    update(order);
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
        del(order * 2 + 1, mid , right);
    }
    update(order);
}

void initArray() {
    int m, i;
    m = 1;
    for (i = 2; i <= rectangle_number * 2; i++) {
        if (hash_number[i - 1] != hash_number[i]) {
            m++;
        }
        hash_number[m] = hash_number[i];
    }
    coor_number = m;
}

int searchIndex(int number) {
    int mid, low, high;
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

    int i, x_1, x_2, y_1, y_2;
    int left, right, total_lenth, pre_lenth, pre_lines;
    scanf("%d", &rectangle_number);
    for (i = 1; i <= rectangle_number * 2; i += 2) {
        scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
        coordinate[i].x = x_1;
        coordinate[i].y_1 = y_1;
        coordinate[i].y_2 = y_2;
        coordinate[i].flag = 0;
        coordinate[i + 1].x = x_2;
        coordinate[i + 1].y_1 = y_1;
        coordinate[i + 1].y_2 = y_2;
        coordinate[i + 1].flag = 1;
        hash_number[i] = y_1;
        hash_number[i + 1] = y_2;
    }
    sort(hash_number + 1, hash_number + rectangle_number * 2 + 1);
    sort(coordinate + 1, coordinate + rectangle_number * 2 + 1, cmp);
    initArray();
    build(1, 1, coor_number);
    left = searchIndex(coordinate[1].y_1);
    right = searchIndex(coordinate[1].y_2);
    insert(1, left, right);
    total_lenth = segment[1].lenth;
    pre_lenth = segment[1].lenth;
    pre_lines = segment[1].lines;
    for (i = 2; i <= rectangle_number * 2; i++) {
        left = searchIndex(coordinate[i].y_1);
        right = searchIndex(coordinate[i].y_2);
        if (!coordinate[i].flag) {
            insert(1, left, right);
        }
        else {
            del(1, left, right);
        }
        total_lenth += abs(segment[1].lenth - pre_lenth);
        total_lenth += pre_lines * (coordinate[i].x - coordinate[i -1 ].x) * 2;
        pre_lenth =segment[1].lenth;
        pre_lines = segment[1].lines;
    }
    printf("%d\n", total_lenth);
    return 0;
}
