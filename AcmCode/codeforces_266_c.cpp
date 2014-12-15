#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;

const int maxn = 500007;
long long val[maxn], sums[maxn];
int pre[maxn];
int last[maxn];
int last_num, n;
int biSearch(int num) {
    int high = last_num;
    int low = 1;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (num < last[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return low;
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    sums[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", &val[i]);
        sums[i] += sums[i - 1] + val[i];
    }
    if (n <= 2 || sums[n] % 3) {
        printf("0\n");
        return 0;
    }
    last_num = 0;
    for (int i = 1; i <= n; i++) {
        if (sums[n] - sums[i - 1] == sums[n] / 3) {
            last[++last_num] = i;
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (sums[i] == sums[n] / 3) {
            long long loc = biSearch(i + 1);
            ans += (last_num - loc + 1);
        }
    }
    printf("%I64d\n", ans);
    return 0;
}

