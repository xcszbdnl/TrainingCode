#include <cstdio>
#include <cstring>

const int maxn = 10007;

int ans[maxn][5];

int main() {
//    freopen("in.txt", "r", stdin);
    int n, k;
    scanf("%d%d", &n, &k);
    ans[0][0] = 1, ans[0][1] = 2, ans[0][2] = 3, ans[0][3] = 5;
//    ans[1][0] = 4, ans[1][1] = 7, ans[1][2] = 9, ans[1][3] = 11;
//    ans[2][0] = 13, ans[2][1] = 14, ans[2][2] = 15, ans[2][3] = 17;
    int max_num = 5;
    for (int i = 1; i <= n; i++) {
        ans[i][0] = max_num + 2;
        ans[i][1] = max_num + 3;
        ans[i][2] = max_num + 4;
        ans[i][3] = max_num + 6;
        max_num = max_num + 6;
    }
    if (n == 1) {
        max_num = 5;
    }
    else {
        max_num -= 6;
    }
    printf("%d\n", max_num * k);
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d\n", ans[i][0] * k, ans[i][1] * k, ans[i][2] * k, ans[i][3] * k);
    }
    return 0;
}
