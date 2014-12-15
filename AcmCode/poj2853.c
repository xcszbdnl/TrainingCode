#include <stdio.h>


int main() {

    int ans, i, number, case_number, test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d", &case_number, &number);
        ans = 0;
        for (i = 1; i * (i + 1) <= number * 2; i++) {
            if ((number - (i - 1) * i / 2) % i == 0) {
                ans++;
            }
        }
        printf("%d %d\n", case_number, ans - 1);
    }
    return 0;
}
