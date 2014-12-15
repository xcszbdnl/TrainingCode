#include <stdio.h>
#include <string.h>

#define MAX_MONEY 100000
#define MAX_DENOMINATION 15

int dp[MAX_DENOMINATION][MAX_MONEY];
int denomination[MAX_DENOMINATION];
int denomination_number[MAX_DENOMINATION];

int main() {

    int  money, number_denomination;
    int i, j, k;
    while (scanf("%d%d", &money, &number_denomination) != EOF) {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (i = 1; i <= number_denomination; i++) {
            scanf("%d%d", &denomination_number[i], &denomination[i]);
        }
        if (!money || !number_denomination) {
            printf("0\n");
            continue;
        }
        for (i = 1; i <= number_denomination; i++) {
            for (j = 0; j <= money; j++) {
                if (dp[i - 1][j]) {
                    for (k = 0; k <= denomination_number[i]; k++) {
                        if (j + k * denomination[i] <= money) {
                            dp[i][j + k * denomination[i]] = dp[i - 1][j];
                        }
                    }
                }
            }
        }
        for (i = money; i >= 0; i--) {
            if (dp[number_denomination][i]) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}
