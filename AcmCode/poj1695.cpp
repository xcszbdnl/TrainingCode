#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 35;
const int INF = 1000006;
int dp[MAX_NUMBER][MAX_NUMBER][MAX_NUMBER];
int maps[MAX_NUMBER][MAX_NUMBER];
int point_number;

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &point_number);
        memset(maps, 0, sizeof(maps));
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= point_number - 1; i++) {
            for (int j = i + 1; j <= point_number; j++) {
                scanf("%d", &maps[i][j]);
            }
        }
        dp[1][1][1] = 0;
        for (int i = 1; i <= point_number - 1; i++) {
            for (int j = 1; j <= i; j++) {
                for (int k = 1; k <= j; k++) {
                    if (dp[i][j][k] != -1) {
                        if (dp[i + 1][j][k] == -1 || dp[i + 1][j][k] > dp[i][j][k] + maps[i][i + 1]) {
                            dp[i + 1][j][k] = dp[i][j][k] + maps[i][i + 1];
                        }
                        if (dp[i + 1][i][j] == -1 || dp[i + 1][i][j] > dp[i][j][k] + maps[k][i + 1]) {
                            dp[i + 1][i][j] = dp[i][j][k] + maps[k][i + 1];
                        }
                        if (dp[i + 1][i][k] == -1 || dp[i + 1][i][k] > dp[i][j][k] + maps[j][i + 1]) {
                            dp[i + 1][i][k] = dp[i][j][k] + maps[j][i + 1];
                        }
                    }
                }
            }
        }
        int min_number = INF;
        for (int i = 1; i <= point_number; i++) {
            for (int k = 1; k <= i; k++) {
                if (dp[point_number][i][k] < min_number && dp[point_number][i][k] != -1) {
                    min_number = dp[point_number][i][k];
                }
            }
        }
        printf("%d\n", min_number);
    }
    return 0;
}
