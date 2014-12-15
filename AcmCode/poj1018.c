#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 105
#define MAX_BANDWIDTH 10005
#define min(a, b) ((a) > (b))?(b) : (a)
#define max(a, b) ((a) > (b))?(a) : (b)

int dp[MAX_NUMBER][MAX_BANDWIDTH];
int bandwidth[MAX_NUMBER];
int price[MAX_NUMBER];


int main() {

    int test_case;
    int i, j, k, device_number, manufacture, max_bandwidth, min_number;
    double ans, temp;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(dp, -1, sizeof(dp));
        scanf("%d", &device_number);
        max_bandwidth = 0;
        for (i = 1; i <= device_number; i++) {
            scanf("%d", &manufacture);
            for (j = 0; j < manufacture; j++) {
                scanf("%d%d", &bandwidth[j], &price[j]);
                if (bandwidth[j] > max_bandwidth) {
                    max_bandwidth = bandwidth[j];
                }
            }
            if (i == 1) {
                dp[i - 1][max_bandwidth] = 0;
            }
            for (j = 1; j <= max_bandwidth; j++) {
                if (dp[i - 1][j] != -1) {
                    for (k = 0; k < manufacture; k++) {
                        min_number = min(j, bandwidth[k]);
                        if (dp[i][min_number] != -1) {
                            dp[i][min_number] = min(dp[i][min_number], dp[i - 1][j] + price[k]);
                        }
                        else {
                            dp[i][min_number] = dp[i - 1][j] + price[k];
                        }
                    }
                }
            }
        }
        ans = 0;
        for (j = 1; j <= max_bandwidth; j++) {
            if (dp[device_number][j] != -1) {
                temp = 1.0 * j / (dp[device_number][j]);
                if (temp > ans) {
                    ans = temp;
                }
            }
        }
        printf("%.3lf\n", ans);
    }
}
