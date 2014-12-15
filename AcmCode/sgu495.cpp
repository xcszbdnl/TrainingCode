#include <cstdio>
#include <cstring>

const int maxn = 100007;

double ans[maxn];
int n, m;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    ans[0] = n * 1.0;
    for (int i = 1; i <= m; i++) {
        ans[i] = ans[i - 1] - ans[i - 1] / n;
    }
    printf("%.9f\n", n - ans[m]);
    return 0;
}
