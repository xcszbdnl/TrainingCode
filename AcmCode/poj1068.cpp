#include <cstdio>
#include <cstring>

const int maxn = 107;

int par[maxn], vis[maxn], ans[maxn];
int main() {
//    freopen("input.txt", "r", stdin);
    int n, test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &n);
        int pre = 0;
        int cnt_loc = 1;
        memset(par, 0, sizeof(par));
        for (int i = 1; i <= n; i++) {
            int temp;
            scanf("%d", &temp);
            for (int j = 1; j <= temp - pre; j++) {
                par[cnt_loc++] = 0;
            }
            pre = temp;
            par[cnt_loc++] = 1;
        }
        cnt_loc--;
//        for (int i = 1; i <= cnt_loc; i++) {
//            printf("%d ", par[i]);
//        }
//        printf("cnt_loc:%d\n", cnt_loc);
        memset(vis, 0, sizeof(vis));
        int ans_number = 0;
        for (int i = 1; i <= cnt_loc; i++) {
            if (par[i] == 1) {
                int number = 1;
                for (int j = i - 1; j >= 1; j--) {
                    if (par[j] == 0 && !vis[j]) {
                        vis[j] = 1;
                        ans[ans_number++] = number;
                        break;
                    }
                    if (par[j] == 0) {
                        number++;
                    }
                }
            }
        }
        for (int i = 0; i < ans_number; i++) {
            printf("%d%s", ans[i], i != ans_number - 1 ? " " : "\n");
        }
//        printf("\n");
    }
    return 0;
}
