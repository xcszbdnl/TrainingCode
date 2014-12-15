#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 100006;

double pro[MAX_NUMBER + 10];

int main() {

    pro[2] = 1;
    pro[4] = 0.5;
    for (int i = 4; i + 2 <= MAX_NUMBER; i += 2) {
        pro[i + 2] = pro[i] * (i - 1) / i;
    }
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        int n;
        scanf("%d", &n);
        double ans = 1 - pro[n];
        printf("%.4lf\n", ans);
    }
    return 0;
}
