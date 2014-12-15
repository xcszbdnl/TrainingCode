#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;
#define MAX_NUMBER 105

struct Point {
    int row;
    int column;
    int height;
};

struct Point point[MAX_NUMBER * MAX_NUMBER];


bool cmp(struct Point a, struct Point b ) {
    return a.height < b.height;
}

int height[MAX_NUMBER][MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];


int main() {

    int row, column, point_number, cnt_row, cnt_column, cnt_height, cnt_lenth, max_lenth;
    int i, j;
    while (scanf("%d%d", &row, &column) != EOF) {
        memset(dp, 0, sizeof(dp));
        memset(height, -1, sizeof(height));
        max_lenth = 1;
        point_number = 0;
        for (i = 1; i <= row; i++) {
            for (j = 1; j <= column; j++) {
                scanf("%d", &height[i][j]);
                point[point_number].row = i;
                point[point_number].column = j;
                point[point_number++].height = height[i][j];
            }
        }
        sort(point, point + point_number, cmp);
        for (i = 0; i < point_number; i++) {
            cnt_row = point[i].row;
            cnt_column = point[i].column;
            cnt_height = point[i].height;
            cnt_lenth = dp[cnt_row][cnt_column];
            if (height[cnt_row][cnt_column - 1] < cnt_height && dp[cnt_row][cnt_column - 1] >= cnt_lenth) {
                dp[cnt_row][cnt_column] = dp[cnt_row][cnt_column - 1] + 1;
                cnt_lenth = dp[cnt_row][cnt_column];
            }
            if (height[cnt_row][cnt_column + 1] < cnt_height && dp[cnt_row][cnt_column + 1] >= cnt_lenth) {
                dp[cnt_row][cnt_column] = dp[cnt_row][cnt_column + 1] + 1;
                cnt_lenth = dp[cnt_row][cnt_column];            
            }
            if (height[cnt_row - 1][cnt_column] < cnt_height && dp[cnt_row - 1][cnt_column] >= cnt_lenth) {
                dp[cnt_row][cnt_column] = dp[cnt_row - 1][cnt_column] + 1;
                cnt_lenth = dp[cnt_row][cnt_column];            
            }
            if (height[cnt_row + 1][cnt_column] < cnt_height && dp[cnt_row + 1][cnt_column] >= cnt_lenth) {
                dp[cnt_row][cnt_column] = dp[cnt_row + 1][cnt_column] + 1;
                cnt_lenth = dp[cnt_row][cnt_column];            
            }
            if (dp[cnt_row][cnt_column] > max_lenth) {
                max_lenth = dp[cnt_row][cnt_column];
            }
        }
        printf("%d\n", max_lenth);
    }
    return 0;
}
