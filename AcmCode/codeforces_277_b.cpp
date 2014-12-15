#include <cstdio>
#include <cstring>

const int maxn = 107;

int maps[maxn][maxn];
int val[maxn][maxn];
int m, n;
int main() {
//    freopen("in.txt", "r", stdin);
    memset(maps, -1, sizeof(maps));
    memset(val, 0, sizeof(val));
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &val[i][j]);
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (val[i][j] == 0) {
                for (int k = 1; k <= n; k++) {
                    maps[i][k] = 0;
                }
                for (int k = 1; k <= m; k++) {
                    maps[k][j] = 0;
                }
            }
        }
    }
    int flag = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (maps[i][j] == -1) {
                maps[i][j] = 1;
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cnt = 0;
            for (int k = 1; k <= n; k++) {
                cnt |= maps[i][k];
            }
            for (int k = 1; k <= m; k++) {
                cnt |= maps[k][j];
            }
            if (cnt != val[i][j]) {
                flag = 1;
                break;
            }
        }
    }
    if (flag) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                printf("%d ", maps[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}
