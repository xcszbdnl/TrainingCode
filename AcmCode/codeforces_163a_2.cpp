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
    for (int i = 1; i <= length_1; i++) {
        for (int j = 1; j <= length_2; j++) {
            dp[i][j] = dp[i][j - 1];
            if (str_1[i - 1] == str_2[j - 1]) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1] + 1) % MOD_NUMBER;
            }
        }
    }
    for (int i = 1; i <= length_1; i++) {
        ans = (ans + dp[i][length_2]) % MOD_NUMBER;
    }
    cout << ans << endl;
    return 0;
}
