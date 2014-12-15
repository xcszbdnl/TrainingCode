#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 5006;
const long long MOD_NUMBER = 1000 * 1000 * 1000 + 7;
char str_1[MAX_NUMBER];
char str_2[MAX_NUMBER];
long long dp[MAX_NUMBER][MAX_NUMBER];
long long ans;
int main() {

    scanf("%s%s", str_1, str_2);
    int length_1 = strlen(str_1);
    int length_2 = strlen(str_2);
    memset(dp, 0, sizeof(dp));
    for (int i = length_1 - 1; i >= 0; i--) {
        for (int j = length_2 - 1; j >= 0; j--) {
            dp[i][j] = dp[i][j + 1];
            if (str_1[i] == str_2[j]) {
                dp[i][j] = (dp[i][j] + dp[i + 1][j + 1] + 1) % MOD_NUMBER;
            }
        }
    }
    for (int i = 0; i <= length_1 - 1; i++) {
        ans = (ans + dp[i][0]) % MOD_NUMBER;
    }
    cout << ans << endl;
    return 0;
}
