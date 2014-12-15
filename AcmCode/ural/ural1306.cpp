#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 25000;
int val[maxn];
int main() {
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val[i]);
    }
    sort(val, val + n);
    if (n % 2) {
        printf("%d\n", val[n / 2]);
    }
    else {
        double ans = val[n / 2 - 1] + val[n / 2];
        ans /= 2;
        printf("%.1lf\n", ans);
    }
    return 0;
}
