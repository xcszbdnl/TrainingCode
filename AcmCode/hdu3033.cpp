#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 107;
struct Product {
    int b,c;
};

struct Product product[20][maxn];
int dp[12][10007];
int num[20];

int n, money, k;

int getMax(int a, int b, int c) {
    int t = a > b ? a : b;
    return t > c ? t : c;
}
int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d%d", &n, &money, &k) != EOF) {
        memset(num, 0, sizeof(num));
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            num[a]++;
            product[a][num[a]].b = b;
            product[a][num[a]].c = c;
        }
        int least_money = 0;
        for (int i = 1; i <= k; i++) {
            int min_number = -1;
            for (int j = 1; j <= num[i]; j++) {
                if (min_number == -1 || product[i][j].b < min_number) {
                    min_number = product[i][j].b;
                }
            }
            least_money += min_number;
        }
        if (money < least_money) {
            printf("Impossible\n");
            continue;
        }
        for (int i = 1; i <= k; i++) {
            for (int m = 1; m <= num[i]; m++) {
                for (int j = money; j >= product[i][m].b; j--) {
                    dp[i][j] = getMax(dp[i][j], dp[i - 1][j - product[i][m].b] + product[i][m].c, dp[i][j - product[i][m].b] + product[i][m].c);
                }
            }
        }
        printf("%d\n", dp[k][money]);
    }
    return 0;
}
