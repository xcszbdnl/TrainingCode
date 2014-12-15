#include <cstdio>
const double PIE = 3.141592654;
int main() {

    int test_case;
    scanf("%d", &test_case);
    int case_number = 1;
    while (test_case--) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        int year = (x * x + y * y) * PIE / 100;
        printf("Property %d: This property will begin eroding in year %d.\n", case_number, year + 1);
        case_number++;
    }
    printf("END OF OUTPUT.\n");
    return 0;
}
