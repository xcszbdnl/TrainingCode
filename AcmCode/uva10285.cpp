#include <string.h>
#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_NUMBER 105

struct Point {
    int row;
    int column;
    int height;
};

struct Point point[MAX_NUMBER * MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];
int maps[MAX_NUMBER][MAX_NUMBER];
int steps[4][2] = {{1,0}, {-1,0}, {0,1}, {0, -1}};
char name[MAX_NUMBER];
int row, column;

bool cmp(struct Point a, struct Point b) {
    return a.height < b.height;
}

int main() {
    freopen("input.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%s%d%d", name, &row, &column);
        memset(dp, 0, sizeof(dp));
        memset(maps, -1, sizeof(maps));
        int point_number = 0;
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= column; j++) {
                int height;
                scanf("%d", &height);
                maps[i][j] = height;
                point[point_number].row = i;
                point[point_number].column = j;
                point[point_number].height = height;
                point_number++;
            }
        }
        sort(point, point + point_number, cmp);
        int max_ans = 1;
        for (int i = 0; i < point_number; i++) {
            int cnt_row = point[i].row;
            int cnt_column = point[i].column;
            int cnt_height = point[i].height;
            int next_row, next_column;
            for (int j = 0; j < 4; j++) {
                next_row = cnt_row + steps[j][0];
                next_column = cnt_column + steps[j][1];
                if (next_row >= 1 && next_row <= row && next_column >= 1 && next_column <= column) {
                    if (maps[next_row][next_column] < cnt_height && dp[cnt_row][cnt_column] < dp[next_row][next_column] + 1) {
                        dp[cnt_row][cnt_column] = dp[next_row][next_column] + 1;
                    }
                    if (max_ans < dp[cnt_row][cnt_column]) {
                        max_ans = dp[cnt_row][cnt_column];
                    }
                }
            }
        }
        printf("%s: %d\n", name, max_ans + 1);
    }
    return 0;
}
