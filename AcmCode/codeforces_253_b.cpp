#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 500007;
using namespace std;

int s[maxn], a[maxn], n, top;
long long ans;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    ans = 0;
    if (n <= 2) {
        printf("0\n");
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        while (top > 1 && s[top - 2] >= s[top - 1] && x >= s[top - 1]) {
            ans = ans + (long long)min(s[top - 2], x);
            top--;
        }
        s[top++] = x;
    }
    sort(s, s + top);
    for (int i = 0; i <= top - 3; i++) {
        ans += s[i];
    }
    printf("%I64d\n", ans);
    return 0;
}
