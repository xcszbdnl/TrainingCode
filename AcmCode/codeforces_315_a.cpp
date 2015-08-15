#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;

const int maxn = 2000007;

int vis[maxn], prime[maxn], phi[maxn], ruo[maxn];
int tmp[maxn], prime_num;
int judgePalindrome(int x) {
    int len = 0;
    while (x) {
        tmp[len++] = x % 10;
        x /= 10;
    }
    for (int i = 0, j = len - 1; i <= j; i++, j--) {
        if (tmp[i] != tmp[j]) {
            return false;
        }
    }
    return true;
}
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
    memset(ruo, 0, sizeof(ruo));
    memset(phi, 0, sizeof(phi));
    vis[1] = 1;
    for (int i = 1; i < maxn; i++) {
        if (!vis[i]) {
            phi[i] = phi[i - 1] + 1;
        }
        else {
            phi[i] = phi[i - 1];
        }
        if (judgePalindrome(i)) {
            ruo[i] = ruo[i - 1] + 1;
        }
        else {
            ruo[i] = ruo[i - 1];
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    getPrime();
//    printf("%d %d\n", phi[maxn - 1], ruo[maxn - 1]);
    int p, q;
    scanf("%d%d", &p, &q);
    int ans = 0;
    for (int i = 1; i < maxn; i++) {
//        printf("%d: %d %d\n", i, phi[i], ruo[i]);
        if (q * phi[i] <= p * ruo[i]) {
            ans = i;
        }
    }
    printf("%d\n", ans);
    return 0;
}
