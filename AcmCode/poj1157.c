#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 105
#define INF 100000

int values[MAX_NUMBER][MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];


int main() {

    int flower_number, vase_number, insert_value, not_insert_value;
    int i, j;
    scanf("%d%d", &flower_number, &vase_number);
    memset(dp, 0, sizeof(dp));
    for (i = 1; i <= flower_number; i++) {
        for (j = 1; j <= vase_number; j++) {
            scanf("%d", &values[i][j]);
        }
    }
    for (i = 1; i <= flower_number; i++) {
        dp[i][0] = -INF;
    }
    for (i = 1; i <= flower_number; i++) {
        for (j = 1; j <= vase_number; j++) {
            insert_value = dp[i - 1][j - 1] + values[i][j];
            not_insert_value = dp[i][j - 1];
            if (insert_value > not_insert_value) {
                dp[i][j] = insert_value;
            }
            else {
                dp[i][j] = not_insert_value;
            }
        }
    }
    printf("%d\n", dp[flower_number][vase_number]);
    return 0;
}
