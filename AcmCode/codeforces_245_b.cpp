#include <cstdio>
#include <cstring>
#include <iostream>

const int maxn = 1007;

using namespace std;
long long val[maxn][maxn];

long long dp_1[maxn][maxn], dp_2[maxn][maxn], dp_3[maxn][maxn], dp_4[maxn][maxn];
int n, m;

long long max(long long a, long long b) {
    return a > b ? a : b;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%I64d", &val[i][j]);
//            printf("%I64d ", val[i][j]);
        }
//        printf("\n");
    }
    memset(dp_1, 0, sizeof(dp_1));
    memset(dp_2, 0, sizeof(dp_2));
    memset(dp_3, 0, sizeof(dp_3));
    memset(dp_4, 0, sizeof(dp_4));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp_1[i][j] = max(dp_1[i - 1][j], dp_1[i][j - 1]) + val[i][j];
//            printf("%I64d ", dp_1[i][j]);
        }
//        printf("\n");
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= m; j++) {
            dp_2[i][j] = max(dp_2[i + 1][j], dp_2[i][j - 1]) + val[i][j];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = m; j >= 1; j--) {
            dp_3[i][j] = max(dp_3[i + 1][j], dp_3[i][j + 1]) + val[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            dp_4[i][j] = max(dp_4[i - 1][j], dp_4[i][j + 1]) + val[i][j];
        }
    }
    long long ans = 0;
    for (int i = 2; i < n; i++) {
        for (int j = 2; j < m; j++) {
            long long temp = dp_1[i][j] + dp_2[i][j] + dp_3[i][j] + dp_4[i][j] - 4 * val[i][j];
            ans = max(ans, temp);
        }
    }
    printf("%I64d\n", ans);
    return 0;
}
