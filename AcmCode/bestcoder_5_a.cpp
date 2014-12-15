#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1007;
const double eps = 1e-10;
double a[maxn], sum;
int n;

int sgn(double x) {
    return x < -eps ? -1 : x > eps;
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lf", &a[i]);
            sum += a[i];
        }
        sort(a + 1, a + 1 + n);
        double median = a[(n + 1) / 2];
        double ave = sum * 1.0 / n;
        if (sgn(ave - median) >= 0) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
        }
    }
    return 0;
}
