#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 105
#define MAX_HEIGHT 5000

int height[MAX_NUMBER];
int dp[MAX_NUMBER][MAX_HEIGHT];

int tower_number;

int main() {

    int test_case, case_number = 0;
    int plus_height, i, j;
    scanf("%d", &test_case);
    while (test_case--) {
        case_number++;
        scanf("%d", &tower_number);
        for (i = 1; i <= tower_number; i++) {
            scanf("%d", &height[i]);
        }
        memset(dp, -1, sizeof(dp));
        dp[0][2500] = 0;
        for (i = 1; i <= tower_number; i++) {
            for (j = 0; j < MAX_HEIGHT; j++) {
                if (dp[i - 1][j] != -1) {
                    plus_height = dp[i - 1][j];
                    if (dp[i][j] < plus_height) {
                        dp[i][j] = dp[i - 1][j];
                    }
                    plus_height = dp[i - 1][j] + height[i];
                    if (dp[i][j + height[i]] < plus_height) {
                        dp[i][j + height[i]] = dp[i - 1][j] + height[i];
                    }
                    plus_height = dp[i - 1][j];
                    if (dp[i][j - height[i]] < plus_height) {
                        dp[i][j - height[i]] = dp[i - 1][j];
                    }
                }
            }
        }
        plus_height = 0;
        for (i = 1; i <= tower_number; i++) {
            if (dp[i][2500] > plus_height) {
                plus_height = dp[i][2500];
            }
        }
        if (plus_height == 0) {
            for (i = 1; i <= tower_number; i++) {
                if (!height[i]) {
                    break;
                }
            }
            if (i <= tower_number) {
                printf("Case %d: 0\n", case_number);
            }
            else {
                printf("Case %d: -1\n", case_number);
            }
        }
        printf("Case %d: %d\n", case_number, dp[tower_number][2500]);
    }
    return 0;
}
