#include <cstdio>
#include <string.h>

int main() {
    long long n;
    long long ans;
    ans = 0;
    scanf("%lld", &n);
    ans = n / 3;
    ans = ans + (n + 1) / 3;
    printf("%lld\n", ans);
    return 0;
}
