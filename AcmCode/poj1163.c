#include <stdio.h>

#define MAX_NUMBER 105
#define INF 1000000
#define max(a, b)  ((a) > (b)) ? (a) : (b)

int data[MAX_NUMBER][MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];



int main() {

    int rows;
    int i, j, max_data;
    scanf("%d", &rows);
    for (i = 1; i <= rows; i++) {
        for (j = 1; j <= i; j++) {
            scanf("%d", &data[i][j]);
        }
    }
    for (i = 1; i <= rows; i++) {
        dp[i][0] = -INF;
    }
    for (i = rows; i >= 1; i--) {
        for (j = 1; j <= i; j++) {
            if (i == rows) {
                dp[rows][j] = data[i][j];
            }
            else {
                max_data = max(dp[i + 1][j], dp[i + 1][j + 1]);
                dp[i][j] = max_data + data[i][j];
            }
        }
    }
    printf("%d\n", dp[1][1]);
}
