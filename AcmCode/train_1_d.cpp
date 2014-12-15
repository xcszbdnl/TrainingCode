#include <cstdio>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAX_NUMBER = 105;

struct Point {
    int x;
    int y;
    int height;
};

int maps[MAX_NUMBER][MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];
int step[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
struct Point point[MAX_NUMBER * MAX_NUMBER];
int row, column, point_number;

bool cmp(struct Point a, struct Point b) {
    return a.height < b.height;
}


int main() {

    scanf("%d%d", &row, &column);
    point_number = 0;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= column; j++) {
            scanf("%d", &maps[i][j]);
            point[point_number].x = i;
            point[point_number].y = j;
            point[point_number].height = maps[i][j];
            point_number++;
        }
    }
    sort(point, point + point_number, cmp);
    memset(dp, 0, sizeof(dp));
    int max_number = 0;
    for (int i = 0; i < point_number; i++) {
        int cnt_x = point[i].x;
        int cnt_y = point[i].y;
        for (int j = 0; j < 4; j++) {
            int next_x = cnt_x + step[j][0];
            int next_y = cnt_y + step[j][1];
            if (next_x >= 1 && next_x <= row && next_y <= column && next_y >= 1 && maps[next_x][next_y] < maps[cnt_x][cnt_y]) {
                if (dp[next_x][next_y] + 1 > dp[cnt_x][cnt_y]) {
                    dp[cnt_x][cnt_y] = dp[next_x][next_y] + 1;
                }
            }
        }
        if (dp[cnt_x][cnt_y] > max_number) {
            max_number = dp[cnt_x][cnt_y];
        }
    }
    printf("%d\n", max_number + 1);
    return 0;
}
