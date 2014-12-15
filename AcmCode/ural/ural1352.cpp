#include <cstdio>
#include <cstring>

const int maxn = 100;

int Mersenne[maxn] = {0,2,3,5,7,13,17,19,31,61,89,107,127,521,607,1279,2203,2281,3217,4253,
4423,9689,9941,11213,19937,21701,23209,44497,86243,110503,132049,216091,756839,859433,1257787,1398269
,2976221,3021377,6972593,13466917,20996011,24036583,25964951,30402457};

int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", pow[n]);
    }
    return 0;
}
