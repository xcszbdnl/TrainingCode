#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1000007;
long long a[maxn];
long long com[100][100];
long long jieceng[100];
int temp[100];
int vis[100];
long long dp[100];
double y = 0.57721566;
int main() {
    while (scanf("%d", &n) != EOF) {
        printf("%.4f\n", y + log(n));
    }
    return 0;
}
