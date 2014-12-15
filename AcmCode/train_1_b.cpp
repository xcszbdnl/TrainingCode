#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 1000;

char string_1[MAX_NUMBER];
char string_2[MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER];
int length_1, length_2;

void solve() {
    for (int i = 1; i <= length_1; i++) {
        for (int j = 1; j <= length_2; j++) {
            if (string_1[i - 1] == string_2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else if (dp[i][j - 1] > dp[i - 1][j]) {
                dp[i][j] = dp[i][j - 1];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
}

int main() {

    while (scanf("%s%s", string_1, string_2) != EOF) {
        memset(dp, 0, sizeof(dp));
        length_1 = strlen(string_1);
        length_2 = strlen(string_2);
        solve();
        printf("%d\n", dp[length_1][length_2]);
    }
}
