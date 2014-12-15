#include <cstdio>
#include <string.h>


#define MAX_NUMBER 105
#define max(a,b) ((a) < (b)) ? (b) : (a)


int dp[MAX_NUMBER][MAX_NUMBER];
int height_1[MAX_NUMBER], height_2[MAX_NUMBER];
int n_1, n_2;

void solve() {
    for (int i = 1; i <= n_1; i++) {
        for (int j = 1; j <= n_2; j++) {
            if (height_1[i] == height_2[j]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
            else if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            }
            else {
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
        }
    }
}


int main() {

    int case_number = 1;
    while (scanf("%d%d", &n_1, &n_2) != EOF) {
        if (!n_1 && !n_2) {
            break;
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n_1; i++) {
            scanf("%d", &height_1[i]);
        }
        for (int i = 1; i <= n_2; i++) {
            scanf("%d", &height_2[i]);
        }
        solve();
        printf("Twin Towers #%d\n", case_number);
        printf("Number of Tiles : %d\n\n", dp[n_1][n_2]);
        case_number++;
    }
    return 0;
}
