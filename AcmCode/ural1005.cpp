#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 2000006;


bool vis[MAX_NUMBER];
int value[30];

int main() {

    memset(vis, 0, sizeof(vis));
    vis[0] = 1;
    int n;
    scanf("%d", &n);
    int sums = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &value[i]);
        sums += value[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = sums; j >= 0; j--) {
            if (vis[j]) {
                vis[j + value[i]] = 1;
            }
        }
    }
    int ans;
    for (int i = sums / 2; i >= 0; i--) {
        if (vis[i]) {
            ans = i;
            break;
        }
    }
    printf("%d\n", sums - 2 * ans);
    return 0;
}
