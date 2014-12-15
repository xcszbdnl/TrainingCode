#include <stdio.h>


int main() {
    int i, ans, number;
    while (scanf("%d", &number) != EOF) {
        ans = 0;
        for (i = 1; i * (i + 1) <= 2 * number; i++) {
            if ((number - i * (i - 1) / 2) % i == 0) {
                ans++;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
