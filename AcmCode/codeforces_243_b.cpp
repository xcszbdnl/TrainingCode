#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 107;

int sums[maxn][maxn], vis[maxn][maxn];
int a[maxn][maxn], m, n, k;


int main() {
//    freopen("in.txt", "r", stdin);
    memset(a, 0, sizeof(a));
    memset(sums, 0, sizeof(sums));
    memset(vis, 0, sizeof(vis));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int ans = 100;
    if (k < n) {
        for (int i = 0; i < n; i++) {
            int num = 0;
            for (int j = 0; j < n; j++) {
                int s1 = 0, s2 = 0;
                for (int k = 0; k < m; k++) {
                    if (a[j][k] == a[i][k]) {
                        s2++;
                    }
                    else {
                        s1++;
                    }
                }
                num += min(s1, s2);
            }
            ans = min(ans, num);
        }
    }
    else {
        for (int i = 0; i < (1 << n); i++) {
            int num = 0;
            for (int j = 0; j < m; j++) {
                int s1 = 0, s2 = 0;
                for (int k = 0; k < n; k++) {
                    int val = 0;
                    if (i & (1 << k)) {
                        val = 1;
                    }
                    if (val == a[k][j]) {
                        s2++;
                    }
                    else {
                        s1++;
                    }
                }
                num += min(s1, s2);
            }
            ans = min(ans, num);
//            printf("%d-->%d\n", ans, i);
        }
    }
    if (ans <= k) {
        printf("%d\n", ans);
    }
    else {
        printf("-1\n");
    }
    return 0;
}
