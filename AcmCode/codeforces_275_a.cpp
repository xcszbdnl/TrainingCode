#include <cstdio>
#include <cstring>

const int maxn = 100007;

int val[maxn], n, k;
int vis[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    memset(vis, 0, sizeof(vis));
    scanf("%d%d", &n, &k);
    if (k == 1) {
        for (int i = 1; i <= n; i++) {
            printf("%d ", i);
        }
        printf("\n");
        return 0;
    }
    val[1] = 1;
    val[2] = n;
    int loc = 3;
    int cnt = 1;
    int last = n - 1;
    int pre = 2;
    while (cnt < k - 1) {
        if (loc % 2 == 0) {
            val[loc++] = last;
            last--;
            cnt++;
        }
        else {
            val[loc++] = pre;
            pre++;
            cnt++;
        }
    }
    if (loc % 2) {
        for (int i = last; i >= pre; i--) {
            val[loc++] = i;
        }
    }
    else {
        for (int i = pre; i <= last; i++) {
            val[loc++] = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", val[i]);
    }
    printf("\n");
    return 0;
}
