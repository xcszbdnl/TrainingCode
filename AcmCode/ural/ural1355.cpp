#include <cstdio>
#include <cstring>
#include <cmath>
const int maxn = 100007;


int vis[maxn], prime[maxn], prime_num;

void getAllPrime() {
    for (int i = 2; i <= sqrt(maxn * 1.0); i++) {
        if (!vis[i]) {
            for (int j = i * 2; j < maxn; j += i) {
                vis[j] = 1;
            }
        }
    }
    prime_num = 0;
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            prime[++prime_num] = i;
        }
    }
}
int main() {
//    freopen("in.txt", "r", stdin);
    getAllPrime();
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        long long a, b;
        scanf("%I64d%I64d", &a, &b);
        if (b % a != 0) {
            printf("0\n");
            continue;
        }
        b /= a;
        long long tmp = b;
        int ans = 1;
        for (int i = 1; i <= prime_num && prime[i] * prime[i] <= b; i++) {
            while (tmp % prime[i] == 0) {
                ans++;
                tmp /= prime[i];
            }
        }
        if (tmp != 1) {
            ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
