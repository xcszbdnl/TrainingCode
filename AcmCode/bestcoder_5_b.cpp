#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 200007;
int n, k;

long long val[maxn];
long long sum = 0;
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &k) != EOF) {
        if (k * (k + 1) / 2 > n) {
            printf("NO\n");
        }
        else {
            printf("YES\n");
        }
    }
}
