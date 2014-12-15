#include <string.h>
#include <cstdio>

const int MAX_NUMBER = 105;
const int INF = 10000000;
int card[MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];
int card_number;

int main() {

    scanf("%d", &card_number);
    for (int i = 1; i <= card_number; i++) {
        scanf("%d", &card[i]);
    }
    for (int i = 1; i <= card_number - 2; i++) {
        dp[i][i + 2] = card[i] * card[i + 1] * card[i + 2];
    }
    for (int length = 4; length <= card_number; length++) {
        for (int i = 1; i + length - 1 <= card_number; i++) {
            int j = i + length - 1;
            dp[i][j] = INF;
            for (int k = i + 1; k <= j - 1; k++) {
                if (dp[i][j] > dp[i][k] + dp[k][j] + card[i] * card[k] * card[j]) {
                    dp[i][j] = dp[i][k] + dp[k][j] + card[i] * card[k] * card[j];
                }
            }
        }
    }
    printf("%d\n", dp[1][card_number]);
}
