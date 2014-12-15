#include <cstdio>
#include <cstring>
#include <cmath>
const int maxn = 10007;
int prime[maxn], prime_num;
int num[maxn], vis[maxn];

void getPrime() {
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= sqrt(maxn + 0.5); i++) {
        if (!vis[i]) {
            for (int j = i + i; j < maxn; j += i) {
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
    getPrime();
    memset(num, 0, sizeof(num));
    for (int i = 1; i <= 10; i++) {
        int a;
        scanf("%d", &a);
        int temp = a;
        for (int j = 1; j <= prime_num && prime[j] * prime[j] <= a; j++) {
            while (temp % prime[j] == 0) {
                num[prime[j]]++;
                temp /= prime[j];
            }
        }
        if (temp != 1) {
            num[temp]++;
        }
    }
    int ans = 1;
    for (int i = 2; i < maxn; i++) {
        num[i]++;
        ans = (ans * num[i]) % 10;
    }
    printf("%d\n", ans);
    return 0;
}
