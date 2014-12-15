#include <cstdio>
#include <cstring>

const int maxn = 100006;
const int INF = 1000000007;
int val[maxn];
int dp_1[maxn], dp_2[maxn];
int n;

int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    if (n == 1 || n == 2) {
        printf("%d\n", n);
        return 0;
    }
    memset(dp_1, 0, sizeof(dp_1));
    memset(dp_2, 0, sizeof(dp_2));
    dp_1[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        if (val[i] < val[i + 1]) {
            dp_1[i] = dp_1[i + 1] + 1;
        }
        else {
            dp_1[i] = 1;
        }
    }
    dp_2[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (val[i] > val[i - 1]) {
            dp_2[i] = dp_2[i - 1] + 1;
        }
        else {
            dp_2[i] = 1;
        }
    }
    int maxn = 0;
    val[n + 1] = INF;
    for (int i = 0; i <= n; i++) {
        if (val[i] < val[i + 2] - 1 && dp_1[i + 2] + dp_2[i] + 1 > maxn) {
            maxn = dp_1[i + 2] + dp_2[i] + 1;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (val[i] >= val[i + 1]) {
            int temp = dp_1[i + 1] + 1;
            if (temp > maxn) {
                maxn = temp;
            }
        }
        else {
            if (maxn < dp_1[i]) {
                maxn = dp_1[i];
            }
        }
    }
    for (int i = n; i >= 1; i--) {
        if (val[i] <= val[i - 1]) {
            int temp = dp_2[i - 1] + 1;
            if (temp > maxn) {
                maxn = temp;
            }
        }
        else {
            if (maxn < dp_2[i]) {
                maxn = dp_2[i];
            }
        }
    }
    if (maxn > n) {
        maxn = n;
    }
    printf("%d\n", maxn);
    return 0;
}
