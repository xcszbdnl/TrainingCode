#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;
int a[maxn];
int vis[maxn], ans[maxn], ans_num;
int n;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) {
                vis[i] = 1;
                int cnt = a[i];
                ans_num = 1;
                ans[0] = i;
                while (cnt != i) {
                    vis[cnt] = 1;
                    ans[ans_num++] = cnt;
                    cnt = a[cnt];
                }
                printf("(%d", ans[0]);
                for (int i = 1; i < ans_num; i++) {
                    printf(" %d", ans[i]);
                }
                printf(")");
            }
        }
        printf("\n");
    }
    return 0;
}
