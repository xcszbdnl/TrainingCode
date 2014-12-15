#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 205;
const int INF = 10000006;
const int BIAS = 500;

int dp[201][21][1007];
int vis[201][21][1007];
int p[MAX_NUMBER], d[MAX_NUMBER];
int ans[MAX_NUMBER];
int n, m, total_d, total_p;
int ans_number;

void getAns(int order, int m, int bias) {
    if (m == 0) {
        return ;
    }
    if (vis[order][m][bias] == 1) {
        total_d += d[order];
        total_p += p[order];
        ans[ans_number++] = order;
        getAns(order - 1, m - 1, bias - p[order] + d[order]);
    }
    else {
        getAns(order - 1, m , bias);
    }
}

int main() {

    int test_case = 1;
    int first = 1;
    while (scanf("%d%d", &n, &m)) {
        if (n == 0 && m == 0) {
            break;
        }
        if (!first) {
            printf("\n");
        }
        ans_number = total_d = total_p = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                for (int k = 0; k < 1007; k++) {
                    dp[i][j][k] = -INF;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &p[i], &d[i]);
        }
        dp[0][0][BIAS] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i && j <= m; j++) {
                for (int k = 0; k < 1007; k++) {
                    dp[i][j][k] = dp[i - 1][j][k];
                    vis[i][j][k] = 0;
                    if (k + d[i] - p[i] > 0 && j > 0) {
                        if (dp[i][j][k] < dp[i - 1][j - 1][k + d[i] - p[i]] + d[i] + p[i]) {
                            dp[i][j][k] = dp[i - 1][j - 1][k + d[i] - p[i]] + d[i] + p[i];
                            vis[i][j][k] = 1;
                        }
                    }
                }
            }
        }
        int min_ans, max_ans, bias;
        max_ans = -1;
        int flag = 0;
        for (int i = 501; i < 1007; i++) {
            if (dp[n][m][i] >= 0) {
                bias = i;
                min_ans = i - BIAS;
                max_ans = dp[n][m][i];
                flag = 1;
                break;
            }
        }
        for (int i = 499; i > 0; i--) {
            if (dp[n][m][i] >= 0) {
                if (flag && BIAS - i <= min_ans) {
                    if (BIAS - i == min_ans) {
                        if (dp[n][m][i] > max_ans) {
                            max_ans = dp[n][m][i];
                            bias = i;
                        }
                    }
                    else {
                        bias = i;
                        min_ans = BIAS - i;
                        max_ans = dp[n][m][i];
                        flag = 1;
                    }
                }
                if (!flag) {
                    bias = i;
                    min_ans = BIAS - i;
                    max_ans = dp[n][m][i];
                    flag = 1;
                }
                break;
            }
        }
        if (!flag || dp[n][m][500] > 0) {
            max_ans = dp[n][m][500];
            bias = 500;
        }
        getAns(n, m, bias);
        printf("Jury #%d\n", test_case);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", total_p, total_d);
        sort(ans, ans + ans_number);
        for (int i = 0; i < ans_number; i++) {
            printf(" %d", ans[i]);
        }
        printf("\n");
        test_case++;
        first = 0;
    }
    return 0;
}
