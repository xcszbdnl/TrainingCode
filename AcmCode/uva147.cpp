#include <cstdio>
#include <string.h>

#define MAX_NUMBER 30005
#define MAX_LENGTH 12

long long dp[MAX_NUMBER];
int coin[MAX_LENGTH] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
int money_10;
double money;

int main() {

    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i <= 10; i++) {
        for (int j = 0; j < MAX_NUMBER; j++) {
            if (j >= coin[i]) {
                dp[j] += dp[j - coin[i]];
            }
        }
    }
    while(scanf("%lf", &money) != EOF) {
        if(money == 0) {
            break;
        }
        money_10 = (int) (money * 100 + 0.5);
        printf("%6.2lf%17lld\n", money, dp[money_10]);
    }
    return 0;
}
