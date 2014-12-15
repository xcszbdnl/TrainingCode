#include <cstdio>
#include <cstring>
#include <cmath>
const double eps = 1e-8;
const int INF = 100000;
double length;
bool test(int cards) {
    double ans = 0;
    for (int i = (cards + 1); i >= 2; i--) {
        ans = ans + 1.0 / i;
    }
    if (ans - length > eps) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {

 
    while (scanf("%lf", &length) != EOF) {
        if (fabs(length) < eps) {
            break;
        }
        int high = INF;
        int low = 1;
        while (low <= high) {
            int mid = (low + high) >> 1;
            if (test(mid)) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        printf("%d card(s)\n", low);
    }
    return 0;
}
