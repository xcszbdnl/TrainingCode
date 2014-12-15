#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
const int maxn = 100;
const double eps = 1e-8;
//const int INF = 1000000000000ll;
long long x[maxn];
int is_left[maxn];
int n;

int sgn(double x) {

}
bool check(double len) {
    memset(is_left, 0, sizeof(is_left));
    x[n + 1] = len + x[n] + 10;
    for (int i = 2; i <= n; i++) {
        if (is_left[i - 1] == 0) {
            if (sgn(x[i] - x[i - 1] - len) >= 0) {
                is_left[i] = 0;
            }
            else if (sgn(x[i + 1] - x[i] - len) >= 0) {
                is_left[i] = 1;
            }
            else {
                return 0;
            }
        }
        else {
            if (sgn(x[i] - x[i - 1] - 2 * len) >= 0) {
                is_left[i] = 0;
            }
            else if (sgn(x[i + 1] - x[i] - len) >= 0) {
                is_left[i] = 1;
            }
            else {
                return 0;
            }
        }
    }
    return 1;
}
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            cin >> x[i];
        }
        sort(x + 1, x + 1 + n);
        double high = x[n] - x[1];
        double low = 0.0;
        while (fabs(high - low) >= eps) {
            double mid = (low + high) / 2;
            if (check(mid)) {
                low = mid;
            }
            else {
                high = mid;
            }
        }
        double ans = low;
        printf("%.3f\n", ans);
    }
    return 0;
}
