#include <cstdio>
#include <cstring>
#include <cmath>

const int maxn = 1000007;

bool vis[maxn];
int prime[maxn], prime_num;

void getAllPrime() {
    for (int i = 2; i <= sqrt(maxn * 1.0); i++) {
        if (!vis[i]) {
            for (int j = i * i; j < maxn; j += i) {
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
//    printf("sadfsadf%d\n", prime_num);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        printf("%d\n", prime[k]);
    }
    return 0;
}
