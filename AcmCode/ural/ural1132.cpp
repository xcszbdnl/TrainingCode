#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;
const int maxn = 100007;

int prime[maxn], prime_num, vis[maxn];

void getAllPrime() {
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < sqrt(maxn * 1.0); i++) {
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
    getAllPrime();
    for (int i = 1; i <= prime_num; i++) {
        if (prime[i] > 32767) {
            printf("%d\n", i);
            printf("%d--->%d\n", i, prime[i]);
            printf("%d--->%d\n", i - 1, prime[i - 1]);
            break;
        }
    }

    return 0;
}
