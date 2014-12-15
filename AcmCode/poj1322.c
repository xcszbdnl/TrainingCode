#include <stdio.h>

#define MAX_NUMBER 1003


double dp[MAX_NUMBER][MAX_NUMBER];

int color_number, take_number, left_number;


int main() {

    int i, j;
    while (scanf("%d", &color_number) != EOF) {
        if (!color_number) {
            break;
        }
        scanf("%d%d", &take_number, &left_number);
        if (left_number > take_number || left_number > color_number || (left_number + take_number) % 2 == 1) {
            printf("0.000\n");
            continue;
        }
        if (take_number > 1000) {
            if (take_number % 2) {
                take_number = 1001;
            }
            else {
                take_number = 1000;
            }
        }
        dp[0][0] = 1;
        for (i = 1; i <= take_number; i++) {
            for (j = 0; j <= i && j <= color_number; j++) {
                if (((i + j) % 2) != 1 ) {
                    dp[i][j] = 0.0;
                    if (j - 1 >= 0) {
                        dp[i][j] += dp[i - 1][j - 1] * ((double)(color_number - j + 1) / color_number);
                    }
                    dp[i][j] += dp[i - 1][j + 1] * ((double)(j + 1) / color_number);
                }
                else {
                    dp[i][j] = 0;
                }
            }
        }
        printf("%.3lf\n", dp[take_number][left_number]);
    }
    return 0;
}
