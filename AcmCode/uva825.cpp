#include <cstdio>
#include <string.h>


#define MAX_NUMBER 100
int dp[MAX_NUMBER][MAX_NUMBER];
int maps[MAX_NUMBER][MAX_NUMBER];
int row, column;

int main() {

    int test_case;
    scanf("%d", &test_case);
    int first = 1;;
    while (test_case--) {
        if (!first) {
            printf("\n");
        }
        scanf("%d%d", &row, &column);
        memset(maps, 0, sizeof(maps));
        memset(dp, 0, sizeof(dp));
        getchar();
        for (int i = 1; i <= row; i++) {
            char one_row[MAX_NUMBER];
            gets(one_row);
            int flag = 0;
            int number = 0;
            int length = strlen(one_row);
            for (int j = 0; j <= length; j++) {
                if (one_row[j] && one_row[j] != ' ') {
                    number = number * 10 + one_row[j] - '0';
                }
                if (!one_row[j] || one_row[j] == ' ') {
                    if (flag) {
                        maps[i][number] = 1;
                    }
                    number = 0;
                    flag = 1;
                }
            }
        }
        dp[1][1] = 1;
        for (int i = 1; i <= row; i++) {
            for (int j = 1; j <= column; j++) {
                if (!maps[i][j - 1]) {
                    dp[i][j] += dp[i][j - 1];
                }
                if (!maps[i - 1][j]) {
                    dp[i][j] += dp[i - 1][j];
                }
            }
        }
        printf("%d\n", dp[row][column]);
        first = 0;
    }
    return 0;
}
