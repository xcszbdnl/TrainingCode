#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;

long long p, q;

long long getSum(long long cnt_number) {
    long long result = 0;
    while (cnt_number) {
        long long m = cnt_number % 10;
        long long sums = cnt_number / 10;
        result += 45 * sums;
        for (int i = 1; i <= m; i++) {
            result += i;
        }
        cnt_number /= 10;
    }
    return result;
}

int main() {

    while (scanf("%lld%lld", &p, &q) != EOF) {
        if (p < 0 && q < 0) {
            break;
        }
        p--;
        long long ans_1, ans_2;
        ans_2 = getSum(q);
        ans_1 = getSum(p);
        printf("%lld\n", ans_2 - ans_1);
    }
    return 0;
}
