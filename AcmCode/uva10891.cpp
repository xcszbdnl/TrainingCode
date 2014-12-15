#include <string.h>
#include <cstdio>

#define MAX_NUMBER 110


int integer[MAX_NUMBER], sums[MAX_NUMBER];
int dp[MAX_NUMBER][MAX_NUMBER], vis[MAX_NUMBER][MAX_NUMBER];
int integer_number;

void search(int start, int end) {
    if (vis[start][end]) {
        return ;
    }
    vis[start][end] = 1;
    int min_ans = 0;
    for (int i = start + 1; i <= end; i++) {
        search(i, end);
        if (dp[i][end] < min_ans) {
            min_ans = dp[i][end];
        }
    }
    for (int i = start; i < end; i++) {
        search(start, i);
        if (dp[start][i] < min_ans) {
            min_ans = dp[start][i];
        }
    }
    dp[start][end] = sums[end] - sums[start - 1] - min_ans;
    return ;
}


int main() {

    while (scanf("%d", &integer_number) != EOF) {
        if (!integer_number) {
            break;
        }
        memset(dp, 0, sizeof(dp));
        memset(vis, 0, sizeof(vis));
        memset(sums, 0, sizeof(sums));
        for (int i = 1; i <= integer_number; i++) {
            scanf("%d", &integer[i]);
            sums[i] = sums[i - 1] + integer[i];
        }
        search(1, integer_number);
        printf("%d\n", 2 * dp[1][integer_number] - sums[integer_number]);
    }
    return 0;
}
