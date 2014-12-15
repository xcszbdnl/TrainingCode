#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 2000007;


int vis[maxn];

long long n;
void getAllPrime() {
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= sqrt(maxn * 1.0); i++) {
        if (!vis[i]) {
            for (int j = i * i; j < maxn; j += i) {
                vis[j] = 1;
            }
        }
    }
}

int isPrime(long long x) {
    for (int i = 2; i <= sqrt(x * 1.0); i++) {
        if (x % i == 0) {
            return 0;
        }
    }
    return true;
}
int main() {
//    freopen("in.txt", "r", stdin);
    getAllPrime();
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%I64d", &n);
        if (isPrime(n)) {
            printf("%I64d\n", n);
            continue;
        }
        if (n % 2 == 0) {
            for (int i = 2; i < maxn; i++) {
                if (!vis[i] && isPrime(n - i)) {
                    printf("%d %I64d\n", i, n - i);
                    break;
                }
            }
        }
        else {
            if (isPrime(n - 2)) {
                printf("2 %I64d\n", n - 2);
                continue;
            }
            n -= 3;
            if (isPrime(n)) {
                printf("3 %I64d\n", n);
                continue;
            }
            for (int i = 2; i < maxn; i++) {
                if (!vis[i] && isPrime(n - i)) {
                    printf("3 %d %I64d\n", i, n - i);
                    break;
                }
            }
        }
    }
    return 0;
}
