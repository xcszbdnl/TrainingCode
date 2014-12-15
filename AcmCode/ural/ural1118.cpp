#include <cstdio>
#include <cstring>

const int maxn = 1000000;

long long cnt_ratio[maxn + 10];


int main() {
//    freopen("in.txt", "r", stdin);
    memset(cnt_ratio, 0, sizeof(cnt_ratio));
    for (int i = 1; i <= maxn; i++) {
        for (int j = 1 ; i * j <= maxn; j++) {
            cnt_ratio[i * j] += i;
        }
    }
    int l, r;
    scanf("%d%d", &l, &r);
    double ans = 1e9;
    int loc = maxn;
    for (int i = l; i <= r; i++) {
        double tmp = cnt_ratio[i] * 1.0 / i;
        if (ans > tmp) {
            loc = i;
            ans = tmp;
        }
    }
    printf("%d\n", loc);
    return 0;
}
