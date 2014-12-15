#include <stdio.h>
#include <string.h>

#define MAX_DEGREE 15001
#define MAX_NUMBER 23

int dp[MAX_NUMBER][MAX_DEGREE];
int location[MAX_NUMBER];
int weight[MAX_NUMBER];

int main() {

    int n, weight_number;
    int i, j , k;
    
    scanf("%d%d", &n, &weight_number);
    for (i = 1; i <= n; i++) {
        scanf("%d", &location[i]);
    }
    
    for (i = 1; i <= weight_number; i++) {
        scanf("%d", &weight[i]);
    }
    
    memset(dp, 0 , sizeof(dp));
    dp[0][7500] = 1;
    
    for (i = 1; i <= weight_number; i++) {
        for (j = 0; j <= 15000; j++) {
            if (dp[i - 1][j]) {
                for (k = 1; k <= n; k++) {
                    dp[i][j + weight[i] * location[k]] += dp[i - 1][j];
                }
            }
        }
    }
    printf("%d\n", dp[weight_number][7500]);
    return 0;
}
