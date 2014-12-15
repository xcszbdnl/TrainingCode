#include <cstdio>
#include <cstring>
#include <cmath>

const int MAX_NUMBER = 100006;
const double eps = 1e-6;

long long g[MAX_NUMBER + 2];
long long dp[MAX_NUMBER + 2];

int main() {

    g[1] = 1;
    for (int i = 2; i < MAX_NUMBER; i++) {
        g[i] = g[i - 1] + ((int)log10(i + eps) + 1);
    }
    for (int i = 1; i < MAX_NUMBER; i++) {
        dp[i] = dp[i - 1] + g[i];
    }
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        int loc;
        scanf("%d", &loc);
        int i = 1;
        while (dp[i] < loc) {
            i++;
        }
        loc -= dp[i - 1];
        i = 1;
        while (g[i] < loc) {
            i++;
        }
        loc -= g[i - 1];
        char temp[10];
        int j =0;
        while (i) {
            temp[j++] = i % 10 + '0';
            i /= 10;
        }
        printf("%c\n", temp[j - loc]);
    }
    return 0;
}
