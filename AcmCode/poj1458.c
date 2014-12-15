#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 1000

char string_x[MAX_NUMBER];
char string_y[MAX_NUMBER];

int dp[MAX_NUMBER][MAX_NUMBER];


void longestCommonSubsequence(int lenth_x, int lenth_y) {
    int i, j;
    for (i = 1; i <= lenth_x; i++) {
        for (j = 1; j <= lenth_y; j++) {
            if (string_x[i - 1] == string_y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                if (dp[i][j - 1] > dp[i - 1][j]) {
                    dp[i][j] = dp[i][j - 1];
                }
                else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
    }
}

int main() {

    int lenth_x, lenth_y;
    while (scanf("%s%s", string_x, string_y) != EOF) {
        memset(dp, 0, sizeof(dp));
        lenth_x = strlen(string_x);
        lenth_y = strlen(string_y);
        longestCommonSubsequence(lenth_x, lenth_y);
        printf("%d\n", dp[lenth_x][lenth_y]);
    }
}
