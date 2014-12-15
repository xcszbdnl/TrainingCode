#include <string.h>
#include <cstdio>

#define MAX_NUMBER 55
#define INF 1000000
#define min(a,b) ((a) > (b)) ? (b) : (a)

int dp[MAX_NUMBER][MAX_NUMBER];

int meter;
int cut_number;
int cut_point[MAX_NUMBER];

int search(int left, int right) {
    if (dp[left][right] != -1) {
        return dp[left][right];
    }
    int min_ans = INF;
    for (int k = left + 1; k <= right - 1; k++) {
        search(left, k);
        search(k, right);
        if (dp[left][k] + dp[k][right] < min_ans) {
            min_ans = dp[left][k] + dp[k][right];
        }
    }
    dp[left][right] = min_ans + cut_point[right] - cut_point[left];
}


int main() {

    while (scanf("%d", &meter) != EOF) {
        if (!meter) {
            break;
        }
        memset(dp, -1, sizeof(dp));
        scanf("%d", &cut_number);
        cut_point[0] = 0;
        cut_point[cut_number + 1] = meter;
        for (int i = 1; i <= cut_number; i++) {
            scanf("%d", &cut_point[i]);
        }
        for (int i = 0; i <= cut_number; i++) {
            dp[i][i + 1] = 0;
            dp[i][i] = 0;
        }
        dp[cut_number + 1][cut_number + 1] = 0;
        search(0, cut_number + 1);
        printf("The minimum cutting is %d.\n", dp[0][cut_number + 1]);
    }
}
