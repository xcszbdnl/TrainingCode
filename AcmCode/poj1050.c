#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 105

int matrix[MAX_NUMBER][MAX_NUMBER];
int sums[MAX_NUMBER][MAX_NUMBER];
int dp[MAX_NUMBER];


int main() {

    int size;
    int i, j, k, column_sum, ans, temp;
    ans = 0;
    scanf("%d", &size);
    for (i = 1; i <= size; i++) {
        for (j = 1; j <= size; j++) {
            scanf("%d", &matrix[i][j]);
            sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i][j];
        }
    }
    for (i = 0; i < size; i++) {
        for (j = i + 1; j <= size; j++) {
            memset(dp, 0, sizeof(dp));
            for (k = 1; k <= size; k++) {
                temp = dp[k - 1];
                column_sum = sums[j][k] - sums[j][k - 1] - sums[i][k] + sums[i][k - 1];
                if (temp > 0) {
                    dp[k] = dp[k - 1] + column_sum;
                }
                else {
                    dp[k] = column_sum;
                }
                if (dp[k] > ans) {
                    ans = dp[k];
                }
            }
        }
    }
    printf("%d\n", ans);
}
