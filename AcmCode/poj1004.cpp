#include <cstdio>

int main() {

    double ans = 0;
    for (int i = 1; i <= 12; i++) {
        double temp;
        scanf("%lf", &temp);
        ans += temp;
    }
    printf("$%.2lf", ans / 12);
    return 0;
}
