#include <cstdio>
#include <cstring>
#include <cmath>

const double eps = 1e-10;

double n, m;
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    while (scanf("%lf%lf", &n, &m) != EOF) {
        double ans;
        if (m == 2) {
            ans = n * (n + 1);
        }
        else {
            ans = 1.0 / (m - 1);
            ans = pow(ans, n);
            ans += n * (m - 2) - 1;
            ans *= m;
            ans /= (m - 2);
            ans /= (m - 2);
        }
        printf("%.10f\n", ans);
    }
    return 0;
}
