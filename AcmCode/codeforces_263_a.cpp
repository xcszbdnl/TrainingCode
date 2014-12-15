#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 300007;

long long ans;
long long val[maxn];
long long sum;
int n;
int main() {
//    freopen("in.txt", "r", stdin);
    ans = sum = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%I64d", &val[i]);
        sum += val[i];
    }
    sort(val + 1, val + 1 + n);
    ans = sum;
    for (int i = 1; i < n; i++) {
        ans += val[i];
        sum -= val[i];
        ans += sum;
    }
    printf("%I64d\n", ans);
    return 0;
}
