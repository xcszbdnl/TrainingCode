#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


const int maxn = 100007;
using namespace std;

int val[maxn];
int n, d;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        if (val[i] <= val[i - 1]) {
            int p = val[i - 1] - val[i];
            ans += (val[i - 1] - val[i]) / d + 1;
            val[i] = ((val[i - 1] - val[i]) / d + 1) * d + val[i];
        }
    }
    printf("%d\n", ans);
    return 0;
}
