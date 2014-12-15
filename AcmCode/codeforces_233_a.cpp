#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

const int maxn = 100007;

char out[maxn];
// 1 1 0
// 1 x ..
// x 1 ..
long long ans, a, b;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%I64d%I64d", &a, &b);
    long long n = min(a, b);
    if (b == 0) {
        ans = a * a;
        printf("%I64d\n", ans);
        for (int i = 1; i <= a; i++) {
            printf("o");
        }
        printf("\n");
        return 0;
    }

    return 0;
}
