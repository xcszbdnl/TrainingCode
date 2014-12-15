#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

const int maxn = 100007;

int prime[maxn], prime_num, vis[maxn], val[maxn];
long long low, high, n;
void getAllPrime() {
    memset(vis, 0, sizeof(vis));
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
    int test_case;
    int ncase = 1;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%I64d%I64d%I64d", &low, &high, &n);
        int len = 0;
        long long temp = n;
        for (int i = 1; i <= prime_num && prime[i] * prime[i] <= temp; i++) {
            if (temp % prime[i] == 0) {
                val[len++] = prime[i];
                while (temp % prime[i] == 0) {
                    temp /= prime[i];
                }
            }
        }
        if (temp != 1) {
            val[len++] = temp;
        }
        long long ans = 0;
        for (int i = 1; i < (1 << len); i++) {
            int c = 0;
            long long num = 1;
            for (int j = 0; j < len; j++) {
                if ((1 << j) & i) {
                    c++;
                    num *= val[j];
                }
            }
            long long cnt_ans = high / num - (low - 1) / num;
            if (c % 2) {
                ans += cnt_ans;
            }
            else {
                ans -= cnt_ans;
            }
        }
        ans = high - low + 1 - ans;
        printf("Case #%d: %I64d\n", ncase++, ans);
    }
    return 0;
}
