#include <cstdio>
#include <cstring>

const int maxn = 1007;

const long long mod_num = 1e9 + 7;
long long a, b, sum;

long long inv(long long num, long long pow) {
    long long ret = 1;
    while (pow) {
        if (pow & 1) {
            ret = (ret * num) % mod_num;
        }
        num = (num * num) % mod_num;
        pow /= 2;
    }
    return ret;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%I64d%I64d", &a, &b);
    sum = 0;
    long long two = inv(2, mod_num - 2);
    for (long long i = 1; i <= b - 1; i++) {
        long long len = a;
        long long first = i;
        long long last = (i * a) % mod_num;
        sum = (sum + (i * len))  % mod_num;
        long long temp = (first + last) % mod_num;
        temp = (temp * len) % mod_num;
        temp = (temp * two) % mod_num;
        temp = (temp * b) % mod_num;
        sum = (sum + temp) % mod_num;
    }
    printf("%I64d\n", (sum + mod_num) % mod_num);
    return 0;
}
