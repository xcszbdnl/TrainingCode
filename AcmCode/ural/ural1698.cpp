#include <cstdio>
#include <cstring>

const int maxn = 2007;

int a[maxn], b[maxn];
int n, ans;


int isOk(int cnt) {
    b[cnt] = 0;
    for (int i = 0; i <= cnt; i++) {
        b[cnt] += a[i] * a[cnt - i];
    }
    if (cnt > 0) {
        b[cnt] += b[cnt - 1] / 10;
    }
    if (b[cnt] % 10 == a[cnt]) {
        return 1;
    }
    return 0;
}
void dfs(int cnt) {
    if (cnt >= n) {
        return ;
    }
    for (int i = 0; i <= 9; i++) {
        a[cnt] = i;
        if (isOk(cnt)) {
            if (a[cnt]) {
                ans++;
            }
            dfs(cnt + 1);
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    ans = 0;
    scanf("%d", &n);
    dfs(0);
    printf("%d\n", ans);
    return 0;
}
