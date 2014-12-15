#include <string.h>
#include <cstdio>


const int MAX_STATE = 310;
const int MAX_COIN = 50;
const int INF = 1000000000;

int dp[MAX_STATE][MAX_STATE];
int convention[MAX_COIN], it[MAX_COIN];

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        int coin_number, goal;
        scanf("%d%d", &coin_number, &goal);
        for (int i = 1; i <= coin_number; i++) {
            scanf("%d%d", &convention[i], &it[i]);
        }
        for (int i = 0; i <= goal; i++) {
            for (int j = 0; j <= goal; j++) {
                dp[i][j] = INF;
            }
        }
        dp[0][0] = 0;
        for (int i = 0; i <= goal; i++) {
            for (int j = 0; j <= goal; j++) {
                for (int k = 1; k <= coin_number; k++) {
                    if (i >= convention[k] && j >= it[k]) {
                        if (dp[i][j] > dp[i - convention[k]][j - it[k]] + 1) {
                            dp[i][j] = dp[i - convention[k]][j - it[k]] + 1;
                        }
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 0; i <= goal; i++) {
            for (int j = 0; j <= goal; j++) {
                if (i * i + j * j == goal * goal) {
                    if (ans > dp[i][j]) {
                        ans = dp[i][j];
                    }
                }
            }
        }
        if (ans == INF) {
            printf("not possible\n");
        }
        else {
            printf("%d\n", ans);
        }
    }
    return 0;
}
