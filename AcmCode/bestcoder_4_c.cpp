#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 109;
//const int INF = 1000000000000ll;
char l[maxn], r[maxn];
int dp[107][20];
int main() {
    freopen("in.txt", "r", stdin);
    scanf("%s%s", l, r);
    for (int i = 0; i <= 9; i++) {
        dp[0][i] = i;
    }
    int r_len = strlen(r);
    for (int i = 1; i <= r_len; i++) {
        for (int j = 0; j <= 9; j++) {
            dp[i][j] = 0;
            for (int k = 0; k <= 9; k++) {
                dp[i][j] += (j - dp[i - 1][k]);
            }
        }
    }
    for (int i = 0; i < r_len; i++) {

    }
    return 0;
}
