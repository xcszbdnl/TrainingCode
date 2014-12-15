#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 310;
const int MAX_COIN = 50;
const int INF = 100000000;
int coin_number;
int convention[MAX_COIN], it[MAX_COIN];
int dp[MAX_NUMBER][MAX_NUMBER];
int goal;

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
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
        for (int i = 1; i <= coin_number; i++) {
            for (int state_1 = convention[i]; state_1 <= goal; state_1++) {
                for (int state_2 = it[i]; state_2 <= goal; state_2++) {
                    if (dp[state_1][state_2] > dp[state_1 - convention[i]][state_2 - it[i]] + 1) {
                        dp[state_1][state_2] = dp[state_1 - convention[i]][state_2 - it[i]] + 1;
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 0; i <= goal; i++) {
            for (int j = 0; j <= goal; j++) {
                if (i * i + j * j == goal * goal) {
                    if (dp[i][j] < ans) {
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

