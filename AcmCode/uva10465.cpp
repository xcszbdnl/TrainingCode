#include <cstdio>
#include <string.h>

#define MAX_NUMBER 10005
#define max(a,b) ((a) > (b)) ? (a) : (b)

int dp[MAX_NUMBER];
int weight[2];
int value_1, value_2, total;

void completePack(int weight, int value) {
    for (int i = weight; i <= total; i++) {
        if (dp[i - weight] != -1) {
            dp[i] = max(dp[i], dp[i - weight] + value);
        }
    }
}
int main() {

    while (scanf("%d%d%d", &value_1, &value_2, &total) != EOF) {
        memset(dp, -1, sizeof(dp));
        weight[0] = value_1;
        weight[1] = value_2;
        dp[0] = 0;
        for (int i = 0; i < 2; i++) {
            completePack(weight[i], 1);
        }
        int i, beer_time = 0;
        for (i = total; i >= 0; i--) {
            if (dp[i] != -1) {
                break;
            }
            beer_time++;
        }
        if (!beer_time) {
            printf("%d\n", dp[i]);
        }
        else {
            printf("%d %d\n", dp[i], beer_time);
        }
    }
    return 0;
}
