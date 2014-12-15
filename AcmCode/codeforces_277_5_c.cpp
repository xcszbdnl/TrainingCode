#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>

int dp[105][1007];
int m, s, ans[107], temp[107], len, biggest;
using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

void getAns(int cnt_len, int sums) {
    if (cnt_len == 0) {
        return ;
    }
    if (biggest < dp[cnt_len][sums]) {
        biggest = dp[cnt_len][sums];
    }
    ans[len++] = dp[cnt_len][sums];
    getAns(cnt_len - 1, sums - dp[cnt_len][sums]);
}
int main() {
//    freopen("in.txt", "r", stdin);
    memset(dp, -1, sizeof(dp));
    scanf("%d%d", &m, &s);
    if (m == 1) {
        if (s >= 0 && s <= 9) {
            printf("%d %d\n", s, s);
        }
        else {
            printf("-1 -1\n");
        }
        return 0;
    }
    dp[0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= s; j++) {
            if (dp[i][j] == -1) {
                continue;
            }
            for (int k = 0; k <= 9; k++) {
                if (dp[i + 1][j + k] == -1 || dp[i + 1][j + k] < k) {
                    dp[i + 1][j + k] = k;
                }
            }
        }
    }
    len = 0;
    if (dp[m][s] == -1) {
        printf("-1 -1\n");
        return 0;
    }
    biggest = 0;
    getAns(m, s);
    if (biggest == 0) {
        printf("-1 -1\n");
        return 0;
    }
    memcpy(temp, ans, sizeof(ans));
    sort(temp, temp + len);
    if (temp[0] == 0) {
        for (int i = 1; i < len; i++) {
            if (temp[i] != 0) {
                temp[0] = 1;
                temp[i]--;
                break;
            }
        }
    }
    for (int i = 0; i < len; i++) {
        printf("%d", temp[i]);
    }
    printf(" ");
    sort(ans, ans + len, cmp);
    for (int i = 0; i < len; i++) {
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
