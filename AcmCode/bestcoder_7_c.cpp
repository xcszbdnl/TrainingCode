#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1007;
int n;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) != EOF) {
        double ans = 0;
        if (n <= 1000000) {
            for (int i = 1; i <= n; i++) {
                double temp = 1.0 / i;
                ans += temp;
            }

        }
        else {
            ans = log(n) + 0.577215664901;
        }
        printf("%.4f\n", ans);
    }
    return 0;
}
