#include <cstdio>
#include <cstring>

const int maxn = 1007;

int ans[maxn], d, left[maxn], right[maxn];

int main() {
//    freopen("input.txt", "r", stdin);
    int n, sums;
    scanf("%d%d", &n, &sums);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &left[i], &right[i]);
    }
    for (int i = 1; i <= n; i++) {
        ans[i] = left[i];
        sums -= left[i];
    }
    if (sums < 0) {
        printf("NO\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        int tmp = right[i] - left[i];
        if (tmp <= sums) {
            ans[i] += tmp;
            sums -= tmp;
        }
        else {
            ans[i] += sums;
            sums = 0;
            break;
        }
    }
    if (sums != 0) {
        printf("NO\n");
        return 0;
    }
    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        printf("%d%s", ans[i], i == n?"\n":" ");
    }
    return 0;
}
