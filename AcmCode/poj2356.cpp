#include <cstdio>
#include <cstring>

const int maxn = 10007;

int n, val[maxn], sums[maxn], vis[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        memset(sums, 0, sizeof(sums));
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        for (int i = 1; i <= n; i++) {
            sums[i] = (sums[i - 1] + val[i]) % n;
            if (sums[i] == 0) {
                printf("%d\n", i);
                for (int j = 1; j <= i; j++) {
                    printf("%d\n", val[j]);
                }
                break;
            }
            if (vis[sums[i]]) {
                printf("%d\n", i - vis[sums[i]]);
                for (int j = vis[sums[i]] + 1; j <= i; j++) {
                    printf("%d\n", val[j]);
                }
                break;
            }
            vis[sums[i]] = i;
        }
    }
    return 0;
}
