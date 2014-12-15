#include <cstdio>
#include <cmath>

const int MAX_NUMBER = 1000006;
const double eps = 1e-10;

unsigned long long value[MAX_NUMBER];

int main() {

    int i = 0;
    while (scanf("%I64u", &value[i]) != EOF) {
        i++;
    }
    for (int j = i - 1; j >= 0; j--) {
        double ans = sqrt(value[j] + eps);
        printf("%.4lf\n", ans);
    }
    return 0;
}
