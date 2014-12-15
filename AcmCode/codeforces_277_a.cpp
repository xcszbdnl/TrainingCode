#include <cstdio>
#include <cstring>

long long n;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%I64d\n", &n);
    if (n % 2) {
        printf("%I64d\n", -n + n / 2);
    }
    else {
        printf("%I64d\n", n / 2);
    }
    return 0;
}
