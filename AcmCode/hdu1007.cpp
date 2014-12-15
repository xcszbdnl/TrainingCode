#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdio.h>

using namespace std;

const int MAX_POINT_NUMBER = 100005;
const double INF = 10000005;
double ans;

struct Point {
    double x;
    double y;
};
int point_number;


double min(double a, double b) {
    return a > b ? b : a;
}

struct Point point[MAX_POINT_NUMBER];
struct Point temp[MAX_POINT_NUMBER];

bool cmpX(struct Point a, struct Point b) {
    return a.x < b.x;
}

bool cmpY(struct Point a, struct Point b) {
    return a.y < b.y;
}

double dist(struct Point point_1, struct Point point_2) {
    double distance = (point_1.x - point_2.x) * (point_1.x - point_2.x) + (point_1.y - point_2.y) * (point_1.y - point_2.y);
    return sqrt(distance);
}


void findNearest(int low, int high) {
    if (high - low == 1) {
        double min_distance = dist(point[low], point[high]);
        ans = min(ans, min_distance);
        return ;
    }
    if (high - low == 2) {
        double distance_1 = dist(point[low] , point[low + 1]);
        double distance_2 = dist(point[low], point[low + 2]);
        double distance_3 = dist(point[low + 1], point[low + 2]);
        ans = min(ans, distance_1);
        ans = min(ans, distance_2);
        ans = min(ans, distance_3);
        return ;
    }
    int mid = (low + high) >> 1;
    findNearest(low, mid);
    findNearest(mid + 1, high);
    int check_point = 0;
    for (int i = low; i <= high; i++) {
        if (point[i].x >= point[mid].x - ans && point[i].x <= point[mid].x + ans) {
            temp[check_point++] = point[i];
        }
    }
    sort(temp, temp + check_point, cmpY);
    for (int i = 0; i < check_point; i++) {
        for (int j = i + 1; j < i + 8 && j < check_point; j++) {
            ans = min(ans, dist(temp[i], temp[j]));
        }
    }
}
int main() {

    while (scanf("%d", &point_number) != EOF) {
        if (!point_number) {
            break;
        }
        for (int i = 0; i < point_number; i++) {
            scanf("%lf%lf", &point[i].x, &point[i].y);
        }
        ans = INF;
        sort(point, point + point_number, cmpX);
        findNearest(0, point_number - 1);
        printf("%.2lf\n", ans / 2);
    }
    return 0;
}
