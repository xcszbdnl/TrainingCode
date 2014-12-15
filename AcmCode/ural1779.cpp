#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_NUMBER = 205;
struct Point {
    int number;
    int degree;
};
struct Point point[MAX_NUMBER];
int n;
int maps[MAX_NUMBER][MAX_NUMBER];
int pairs;
bool cmp(struct Point a, struct Point b) {
    return a.degree > b.degree;
}
int main() {

    scanf("%d", &n);
    if (n == 3) {
        printf("1\n");
        printf("1 2\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        point[i].number = i;
        point[i].degree = n - 1 - (i - 1) / 2;
    }
    if (n % 2 == 1) {
        if ((n - 1 - (n - 1) / 2) % 2 == 1) {
            point[n].degree--;
        }
    }
    memset(maps, 0, sizeof(maps));
    pairs = 0;
    for (int i = 1; i <= n; i++) {
        sort(point + i, point + n + 1, cmp);
        if (point[i].degree == 0) {
            break;
        }
        for (int j = i + 1; point[i].degree > 0; j++) {
            point[i].degree--;
            point[j].degree--;
            maps[point[i].number][point[j].number] = 1;
            pairs++;
        }
    }
    printf("%d\n", pairs);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (maps[i][j]) {
                printf("%d %d\n", i, j);
            }
        }
    }
    return 0;
}
