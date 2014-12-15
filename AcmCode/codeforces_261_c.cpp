#include <cstdio>
#include <cstring>

const int maxn = 1007;

int ans[maxn][maxn];
int n, k, d;
int temp[maxn];

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &n, &k, &d);
    long long cnt = 1;
    int flag = 0;
    for (int i = 1; i <= d; i++) {
        if (cnt >= n) {
            flag = 1;
            break;
        }
        cnt = cnt * k;
    }
    if (cnt < n && !flag) {
        printf("-1");
        return 0;
    }
    for (int i = 1; i <= d; i++) {
        for (int j = 1; j <= n; j++) {
            ans[i][j] = 1;
        }
    }
    for (int i = 1; i <= d; i++) {
        temp[i] = 1;
    }
    for (int i = 2; i <= n; i++) {
        temp[1]++;
        int next = 0;
        for (int j = 1; j <= d; j++) {
            if ((temp[j] + next) >= k + 1) {
                temp[j] = 1;
                next = 1;
            }
            else {
                temp[j] = temp[j] + next;
                break;
            }
        }
        for (int j = 1; j <= d; j++) {
            ans[j][i] = temp[j];
        }
    }
    for (int i = 1; i <= d; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
