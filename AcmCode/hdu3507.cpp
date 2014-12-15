#include <cstdio>
#include <cstring>


const int maxn = 1000007;
int que[maxn];

long long dp[maxn];
long long sum[maxn];
int n, m;

long long getUp(int i, int j) {
    return dp[i] + sum[i] * sum[i] - dp[j] - sum[j] * sum[j];
}

long long getDown(int i, int j) {
    return 2 * (sum[i] - sum[j]);
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(sum, 0, sizeof(sum));
        memset(dp, 0, sizeof(dp));
        int head = 0;
        int rear = 0;
        que[rear++] = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            sum[i] = sum[i - 1] + x;
            while (head + 1 < rear && getUp(que[head + 1], que[head]) <= sum[i] * getDown(que[head + 1], que[head])) {
                head++;
            }
            dp[i] = dp[que[head]] + (sum[i] - sum[que[head]]) * (sum[i] - sum[que[head]]) + m;
            while (head + 1 < rear && getUp(i, que[rear - 1]) * getDown(que[rear - 1], que[rear - 2]) <= getUp(que[rear - 1], que[rear - 2]) * getDown(i, que[rear - 1])) {
                rear--;
            }
            que[rear++] = i;
        }
        printf("%d\n", dp[n]);
    }
    return 0;
}
