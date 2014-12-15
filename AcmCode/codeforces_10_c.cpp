#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 1000007;
long long ans;
long long n;
long long d[maxn], num[maxn];

int getD(int x) {
    while (x > 9) {
        int temp = x;
        int sums = 0;
        while (temp) {
            sums += temp % 10;
            temp /= 10;
        }
        x = sums;
    }
    return x;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%I64d", &n);
    for (int i = 1; i <= n; i++) {
        d[i] = getD(i);
        num[d[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        ans -= n / i;
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            ans += num[i] * num[j] * num[getD(i * j)];
        }
    }
    printf("%I64d\n", ans);
    return 0;
}
