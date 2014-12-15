#include <cstdio>
#include <string.h>
#include <queue>


using namespace std;

const int MAX_NUMBER = 100005;

struct Point {
    int x;
    int y;
    Point(double x_1 = 0, double y_1 = 0) {
        x = x_1;
        y = y_1;
    }
};



struct Line {
    double x_1;
    double y_1;
    double x_2;
    double y_2;
};

Point operator - (struct Point a, struct Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

queue<int> lines;
struct Line input[MAX_NUMBER];
int line_number;

double getCross(struct Point a, struct Point b) {
    return a.x * b.y - a.y * b.x;
}

int judgeIntersection(int line_1, int line_2) {
    Point a_1, a_2, b_1, b_2;
    a_1.x = input[line_1].x_1;
    a_1.y = input[line_1].y_1;
    a_2.x = input[line_1].x_2;
    a_2.y = input[line_1].y_2;
    b_1.x = input[line_2].x_1;
    b_1.y = input[line_2].y_1;
    b_2.x = input[line_2].x_2;
    b_2.y = input[line_2].y_2;
    double c_1 = getCross(a_2 - a_1, b_1 - a_1);
    double c_2 = getCross(a_2 - a_1, b_2 - a_1);
    double c_3 = getCross(b_2 - b_1, a_1 - b_1);
    double c_4 = getCross(b_2 - b_1, a_2 - b_1);
    return c_1 * c_2 < 0 && c_3 * c_4 < 0;
}


int main() {

    while (scanf("%d", &line_number) != EOF) {
        if (line_number == 0) {
            break;
        }
        for (int i = 1; i <= line_number; i++) {
            scanf("%lf%lf%lf%lf", &input[i].x_1, &input[i].y_1, &input[i].x_2, &input[i].y_2);
        }
        lines.push(1);
        for (int i = 2; i <= line_number; i++) {
            int first = -1;
            while (!lines.empty()) {
                int cnt_line = lines.front();
                lines.pop();
                if (!judgeIntersection(i, cnt_line)) {
                    if (first == -1) {
                        first = cnt_line;
                    }
                    lines.push(cnt_line);
                }
                if (lines.front() == first) {
                    break;
                }
            }
            lines.push(i);
        }
        printf("Top sticks: %d", lines.front());
        lines.pop();
        while (!lines.empty()) {
            printf(", %d", lines.front());
            lines.pop();
        }
        printf(".\n");
    }
    return 0;
}
