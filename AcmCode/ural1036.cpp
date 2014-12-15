#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 1006;
const int MAX_N = 105;

long long dp[MAX_N][MAX_NUMBER];
int n, s;

int main() {

    scanf("%d%d", &n, &s);
    if (s % 2 != 0) {
        printf("0\n");
        return 0;
    }
    s /= 2;
    for (int i = 0; i <= 9; i++) {
        dp[1][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= s; j++) {
            for (int k = 0; k <= 9; k++) {
                if (j >= k) {
                    dp[i][j] += dp[i - 1][j - k];
                }
            }
        }
    }
    cout << dp[n][s] * dp[n][s] << endl;
    return 0;
}
