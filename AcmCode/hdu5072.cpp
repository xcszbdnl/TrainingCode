#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 100007;

int prime[maxn], prime_num, vis[maxn], val[maxn];
int num[maxn], n;
long long ans;


void getAllPrime() {
    prime_num = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= sqrt(maxn * 1.0); i++) {
        if (!vis[i]) {
            for (int j = i + i; j < maxn; j += i) {
                vis[j] = 1;
            }
        }
    }
    for (int i = 2; i < maxn; i++) {
        if (!vis[i]) {
            prime[++prime_num] = i;
        }
    }
}

void init() {
    for (int i = 1; i <= n; i++) {
        int temp = val[i];
        int s[100];
        int s_num = 0;
        for (int j = 1; j <= prime_num && prime[j] * prime[j] <= temp; j++) {
            if (temp % prime[j] == 0) {
                s[s_num++] = prime[j];
                while (temp % prime[j] == 0) {
                    temp /= prime[j];
                }
            }
        }
        if (temp != 1) {
            s[s_num++] = temp;
        }
        for (int j = 1; j < (1 << s_num); j++) {
            int cnt = 1;
            for (int k = 0; k < s_num; k++) {
                if (j & (1 << k)) {
                    cnt *= s[k];
                }
            }
            num[cnt]++;
        }
    }
}

void cal() {
    ans = (long long)n * (n - 1) * (n - 2) / 6;
    long long sums = 0;
    for (int i = 1; i <= n; i++) {
        int temp = val[i];
        int s[100];
        int s_num = 0;
        for (int j = 1; j <= prime_num && prime[j] * prime[j] <= temp; j++) {
            if (temp % prime[j] == 0) {
                s[s_num++] = prime[j];
                while (temp % prime[j] == 0) {
                    temp /= prime[j];
                }
            }
        }
        if (temp != 1) {
            s[s_num++] = temp;
        }
        long long ret = 0;
        for (int j = 1; j < (1 << s_num); j++) {
            int cnt = 1;
            int k_num = 0;
            for (int k = 0; k < s_num; k++) {
                if (j & (1 << k)) {
                    cnt *= s[k];
                    k_num++;
                }
            }
            if (k_num % 2) {
                ret += num[cnt];
            }
            else {
                ret -= num[cnt];
            }
        }
        if (ret == 0) {
            continue;
        }
        sums += (n - ret) * (ret - 1);
    }
    ans -= sums / 2;
    printf("%I64d\n", ans);
}
int main() {
//    freopen("in.txt", "r", stdin);
    getAllPrime();
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(num, 0, sizeof(num));
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &val[i]);
        }
        init();
        cal();
    }
    return 0;
}
