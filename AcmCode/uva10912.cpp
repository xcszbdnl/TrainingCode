#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 10005;


long long dp[30][MAX_NUMBER][30];
int s, l;

int main() {

    int case_number = 1;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= 26; i++) {
        dp[1][i][i] = 1;
    }
    for (int i = 2; i <= 26; i++) {
        for (int j = 1; j <= 10000; j++) {
            for (int k = 1; k <= 26 && k <= j; k++) {
                for (int m = 1; m < k; m++) {
                    dp[i][j][k] += dp[i - 1][j - k][m];
                }
            }
        }
    }
    while (scanf("%d%d", &l, &s) != EOF) {
        if (!l && !s) {
            break;
        }
        if (l > 26) {
            printf("Case %d: 0\n", case_number);
            case_number++;
            continue;
        }
        long long ans = 0;
        for (int i = 1; i <= 26; i++) {
            ans += dp[l][s][i];
        }
        printf("Case %d: %ld\n", case_number, ans);
        case_number++;
    }
    return 0;
}
