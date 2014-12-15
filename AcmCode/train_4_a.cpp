#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 10005;

struct Point {
    double x;
    double y;
};

struct Line {
    struct Point a;
    struct Point b;
};

struct Line line[MAX_NUMBER];
int bin[MAX_NUMBER];
int bin_number, toy_number, top, down, left, right, line_number;

double getCross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

int isLeft(int order, int x, int y) {
    Point u, v;
    v.x = x - line[order].a.x;
    v.y = y - line[order].a.y;
    u.x = line[order].b.x - line[order].a.x;
    u.y = line[order].b.y - line[order].a.y;
    double flag = getCross(v, u);
    if (flag > 0) {
        return 0;
    }
    else {
        return 1;
    }
}

int binarySearch(int x, int y) {
    int low = 1;
    int high = bin_number + 2;
    while (high - low != 1) {
        int mid = (high + low) >> 1;
        int left = isLeft(mid, x, y);
        if (left == 1) {
            high = mid;
        }
        else {
            low = mid;
        }
    }
    return low;
}

int main() {

    int first = 1;
    while (scanf("%d", &bin_number) != EOF) {
        if (!bin_number) {
            break;
        }
        scanf("%d%d%d%d%d", &toy_number, &left, &top, &right, &down);
        if (!first) {
            printf("\n");
        }
        line_number = 2;
        memset(bin, 0, sizeof(bin));
        line[1].a.x = left;
        line[1].a.y = down;
        line[1].b.x = left;
        line[1].b.y = top;
        for (int i = 2; i <= bin_number + 1; i++) {
            scanf("%lf%lf", &line[i].b.x, &line[i].a.x);
            line[i].a.y = down;
            line[i].b.y = top;
        }
        line[bin_number + 2].a.x = right;
        line[bin_number + 2].a.y = down;
        line[bin_number + 2].b.x = right;
        line[bin_number + 2].b.y = top;
        for (int i = 1; i <= toy_number; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            int low = binarySearch(x, y);
            low--;
            bin[low]++;
        }
        for (int i = 0; i <= bin_number; i++) {
            printf("%d: %d\n", i, bin[i]);
        }
        first = 0;
    }
    return 0;
}
