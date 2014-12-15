#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 205;

long long dp[MAX_NUMBER][25][25];
int number[MAX_NUMBER];
int n, q, d, m;

int main() {

    int case_number = 1;
    while (scanf("%d%d", &n, &q) != EOF) {
        if (!n && !q) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", &number[i]);
        }
        printf("SET %d:\n", case_number);
        case_number++;
        for (int query_number = 1; query_number <= q; query_number++) {
            scanf("%d%d", &d, &m);
            memset(dp, 0, sizeof(dp));
            dp[1][1][((number[1] % d) + d) % d] = 1;
            dp[1][0][0] = 1;
            for (int i = 1; i < n; i++) {
                for (int j = 0; j <= i && j <= m; j++) {
                    for (int s = 0; s < d; s++) {
                        if (dp[i][j][s]) {
                            long long temp = ((((s + number[i + 1]) % d)) + d) %d;
                            dp[i + 1][j + 1][temp] += dp[i][j][s];
                            dp[i + 1][j][s] += dp[i][j][s];
                        }
                    }
                }
            }
            printf("QUERY %d: %lld\n", query_number, dp[n][m][0]);
        }
    }
    return 0;
}
