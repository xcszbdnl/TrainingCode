#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 15

int dp[MAX_NUMBER][MAX_NUMBER];

int main() {

    int test_case;
    int apple_number, plate_number;
    int i, j;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d", &apple_number, &plate_number);
        memset(dp, 0, sizeof(dp));
        for (i = 0; i <= apple_number; i++) {
            dp[1][i] = 1;
            dp[0][i] = 1;
        }
        for (i = 0; i <= plate_number; i++) {
            dp[i][0] = 1;
            dp[i][1] = 1;
        }
        for (i = 2; i <= plate_number; i++) {
            for (j = 2; j <= apple_number; j++) {
                if (i > j) {
                    dp[i][j] = dp[j][j];
                }
                else {
                    dp[i][j] += dp[i - 1][j];
                    dp[i][j] += dp[i][j - i];
                }
            }
        }
        printf("%d\n", dp[plate_number][apple_number]);
    }
}
