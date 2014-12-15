#include <cstdio>
#include <cstring>

const int maxn = 100007;
int a[maxn];
int n;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int loc = n + 1;
    for (int i = 1; i <= n; i++) {
        if (i < n && a[i] > a[i + 1])  {
            loc = i + 1;
            break;
        }
    }
    int ans = n - loc + 1;
    int flag = 0;
    for (int i = loc; i <= n; i++) {
        if (i < n && a[i] > a[i + 1]) {
            flag = 1;
            break;
        }
    }
    if (ans != 0 && a[n] > a[1]) {
        flag = 1;
    }
    if (flag) {
        printf("-1\n");
    }
    else {
        printf("%d\n", ans);
    }
    return 0;
}
