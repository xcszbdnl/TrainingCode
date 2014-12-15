#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_POINT = 10;

struct Point {
    double x;
    double y;
    Point(double x = 0, double y = 0) : x(x), y(y){}
};

struct Point operator - (struct Point a, struct Point b) {
    return Point(a.x - b.x, a.y - b.y);
}
struct Point operator + (struct Point a, struct Point b) {
    return Point(a.x + b.x, a.y + b.y);
}
struct Point operator * (struct Point a, double b) {
    return Point (a.x * b, a.y * b);
}

struct Point rotate(struct Point a, double angle) {
    return Point(a.x * cos(angle) - a.y * sin(angle), a.x * sin(angle) + a.y * cos(angle));
}

double getCross(struct Point a, struct Point b) {
    return a.x * b.y - a.y * b.x;
}

double getLength(struct Point a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

double Dot(struct Point a, struct Point b) {
    return a.x * b.x + a.y * b.y;
}

double getAngle(struct Point a, struct Point b) {
    return acos(Dot(a, b) / getLength(a) / getLength(b));
}

struct Point getIntersection(struct Point a, struct Point d_1, struct Point b, struct Point d_2) {
    struct Point u = a - b;
    double t = getCross(d_2, u) / getCross(d_1, d_2);
    return a + d_1 * t;
}

struct Point getPoint(struct Point a, struct Point b, struct Point c) {
    struct Point v_1, v_2;
    v_1 = c - b;
    double angle = getAngle(v_1, a - b);
    v_1 = rotate(v_1, angle / 3);

    v_2 = b - c;
    angle = getAngle(v_2, a - c);
    v_2 = rotate(v_2, -angle / 3);
    return getIntersection(b, v_1, c, v_2);
}

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        struct Point a, b, c, d, e, f;
        scanf("%lf%lf", &a.x, &a.y);
        scanf("%lf%lf", &b.x, &b.y);
        scanf("%lf%lf", &c.x, &c.y);
        d = getPoint(a, b, c);
        e = getPoint(b, c, a);
        f = getPoint(c, a, b);
        printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n", d.x, d.y, e.x, e.y, f.x, f.y);
    }
    return 0;
}
