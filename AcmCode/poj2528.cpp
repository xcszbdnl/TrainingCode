#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>

#define MAX_NUMBER 20005

using namespace std;

struct Segment {
    int left;
    int right;
    int color;
};

struct Segment segment[MAX_NUMBER * 4];
int hash_number[MAX_NUMBER];
int insert_number[MAX_NUMBER], ans;
int vis[MAX_NUMBER];
int people_number, coor_number;

void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].color = 0;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void insert(int order, int left, int right, int color) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (left <= segment[order].left && right >= segment[order].right) {
        segment[order].color = color;
        return ;
    }
    if (segment[order].color) {
        segment[order * 2].color = segment[order * 2 + 1].color = segment[order].color;
        segment[order].color = 0;
    }
    if (right <= mid) {
        insert(order * 2, left, right, color);
    }
    else if (left > mid) {
        insert(order * 2 + 1, left, right, color);
    }
    else {
        insert(order * 2, left, mid, color);
        insert(order * 2 + 1, mid + 1, right, color);
    }
}

void query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2; 
    if (segment[order].color) {
        if (!vis[segment[order].color]) {
            ans++;
            vis[segment[order].color] = 1;
        }
        return ;
    }
    if (segment[order].left == segment[order].right) {
        return ;
    }
    if (right <= mid) {
        query(order * 2, left, right);
    }
    else if (left > mid) {
        query(order * 2 + 1, left, right);
    }
    else {
        query(order * 2, left, mid);
        query(order * 2 + 1, mid + 1, right);
    }
}

void init() {
    int i, m;
    m = 1;
    for (i = 2; i <= people_number * 2; i++) {
        if (hash_number[i - 1] != hash_number[i]) {
            m++;
        }
        hash_number[m] = hash_number[i];
    }
    coor_number = m;
}

int searchIndex(int number) {
    int mid, high, low;
    low = 1;
    high = coor_number;
    while (low <= high) {
        mid = (low + high) / 2;
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

    int test_case, i, left, right;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &people_number);
        ans = 0;
        memset(vis, 0, sizeof(vis));
        for (i = 1; i <= people_number * 2; i += 2) {
            scanf("%d%d", &left, &right);
            insert_number[i] = left;
            insert_number[i + 1] = right;
            hash_number[i] = left;
            hash_number[i + 1] = right;
        }
        sort(hash_number + 1, hash_number + people_number * 2 + 1);
        init();
        build(1, 1, coor_number);
        for (i = 1; i <= people_number * 2; i += 2) {
            left = searchIndex(insert_number[i]);
            right = searchIndex(insert_number[i + 1]);
            insert(1, left, right, i);
        }
        query(1, 1, coor_number);
        printf("%d\n", ans);
    }
}
