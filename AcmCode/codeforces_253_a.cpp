#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 107;
const double eps = 1e-6;
const double const_pro = 0.5;

double dp[maxn][5];
double pro[maxn];
int n;

bool cmp(double a, double b) {
    return a > b;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf", &pro[i]);
    }
    sort(pro + 1, pro + 1 + n, cmp);
    if (pro[1] > const_pro) {
        printf("%.12lf\n", pro[1]);
    }
    else {
        dp[0][0] = 1.0;
        dp[0][1] = 0.0;
        dp[0][2] = 0.0;
        int ans = n;
        for (int i = 1; i <= n; i++) {
            dp[i][0] = dp[i - 1][0] * (1 - pro[i]);
            dp[i][1] = dp[i - 1][0] * pro[i] + dp[i - 1][1] * (1 - pro[i]);
            if (dp[i][1] < dp[i - 1][1]) {
                ans = i - 1;
                break;
            }
        }
        printf("%.12lf\n", dp[ans][1]);
    }
    return 0;
}

