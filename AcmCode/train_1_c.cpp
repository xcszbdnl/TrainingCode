#include <string.h>
#include <cstdio>

const int MAX_NUMBER = 15;

int dp[MAX_NUMBER][MAX_NUMBER];
int apple, plate;

void search(int a, int p) {
    if (dp[a][p] != -1) {
        return ;
    }
    if (a == 0 || a == 1) {
        dp[a][p] = 1;
        return ;
    }
    if (p == 0 || p == 1) {
        dp[a][p] = 1;
        return ;
    }
    if (a < p) {
        search(a, a);
        dp[a][p] = dp[a][a];
        return ;
    }
    else {
        search(a - p, p);
        search(a, p -1);
        dp[a][p] = dp[a - p][p] + dp[a][p - 1];
    }
}

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d", &apple, &plate);
        memset(dp, -1, sizeof(dp));
        search(apple, plate);
        printf("%d\n", dp[apple][plate]);
    }
    return 0;
}
