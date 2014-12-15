#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_NUMBER = 20;

int maps[MAX_NUMBER][MAX_NUMBER];
int value[MAX_NUMBER];

struct Point {
    int degree;
    int number;
};
int point_number;

bool cmp(struct Point a, struct Point b) {
    return a.degree > b.degree;
}
struct Point point[MAX_NUMBER];
int main() {

    int test_case;
    scanf("%d", &test_case);
    int first = 1;
    while (test_case--) {
        if (!first) {
            printf("\n");
        }
        scanf("%d", &point_number);
        memset(maps, 0, sizeof(maps));
        int flag = 0;
        for (int i = 1; i <= point_number; i++) {
            point[i].number = i;
            scanf("%d", &point[i].degree);
        }
        for (int i = 1; i <= point_number; i++) {
            sort(point + i, point + 1 + point_number, cmp);
            if (point[point_number].degree < 0) {
                flag = 1;
                break;
            }
            if (point[i].degree == 0) {
                break;
            }
            else {
                for (int j = i + 1; point[i].degree > 0; j++) {
                    point[i].degree--;
                    point[j].degree--;
                    maps[point[i].number][point[j].number] = 1;
                    maps[point[j].number][point[i].number] = 1;
                }
            }
        }
        if (flag) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
            for (int i = 1; i <= point_number; i++) {
                for (int j = 1; j <= point_number; j++) {
                    if (j == 1) {
                        printf("%d", maps[i][j]);
                    }
                    else {
                        printf(" %d", maps[i][j]);
                    }
                }
                printf("\n");
            }
        }
        first = 0;
    }
}
