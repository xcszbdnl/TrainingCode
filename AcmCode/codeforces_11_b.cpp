#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;

long long x;

//1 + 2 + 3 + ... + n == a > x
//1 + 2 + 3 + ... + n - 1 < x
//a - x = c < n
//c == 2 * s
//1 + 2 + 3 + ... -c
long long sums;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%I64d", &x);
    if (x < 0) {
        x = -x;
    }
    if (x == 0) {
        printf("0\n");
        return 0;
    }
    sums = 0;
    int i;
    for(i = 0; sums < x; i++) {
        sums += i;
    }
    i--;
    if (sums == x) {
        printf("%d\n", i);
    }
    else {
        long long p = sums - x;
        while (p % 2) {
            i++;
            sums += i;
            p = sums - x;
        }
        printf("%d\n", i);
    }
    return 0;
}
