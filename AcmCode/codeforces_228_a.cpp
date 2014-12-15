#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 107;

int piles[maxn][maxn];
int piles_num[maxn];
int val[maxn], num[maxn], flag[maxn];
int n;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    memset(piles_num, 0, sizeof(piles_num));
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }
    sort(val + 1, val + 1 + n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (val[i] >= piles_num[j]) {
                piles_num[j]++;
                break;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (piles_num[i]) {
            ans++;
        }
    }
//    int ans = 0;
    printf("%d\n", ans);
    return 0;
}
