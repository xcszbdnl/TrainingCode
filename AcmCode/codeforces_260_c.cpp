#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define max(a,b) ((a) > (b)) ? (a) : (b)
const int maxn = 100007;
const int INF = 10000007;
long long val[maxn], num[maxn], dp[maxn];
int n, maxval;
long long temp[2];
long long ans;

void dfs(int cnt) {
    if (dp[cnt] != -1) {
        return ;
    }
    dp[cnt] = 0;
    if (cnt > maxval) {
        return ;
    }
    dp[cnt] = 0;
    dfs(cnt + 2);
    dfs(cnt + 1);
    dp[cnt] = max(dp[cnt + 2] + num[cnt] * cnt, dp[cnt + 1]);
}
int main() {
//    freopen("in.txt", "r", stdin);
    memset(num, 0, sizeof(num));
    memset(dp, -1, sizeof(dp));
    scanf("%d", &n);
    maxval = 0;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        num[val[i]]++;
        if (maxval <= val[i]) {
            maxval = val[i];
        }
    }
    dfs(0);
    int flag = 0;
    int i;
    ans = 0;
    printf("%I64d\n", dp[0]);
    return 0;
}
