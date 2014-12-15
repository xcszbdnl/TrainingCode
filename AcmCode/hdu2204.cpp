#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>

const int maxn = 10000;
const double eps = 1e-8;

int vis[maxn], prime[maxn], prime_num;
long long n;
int sgn(double x) {
    return x < -eps ? -1 : x > eps;
}
void getAllPrime() {
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < 100; i++) {
        if (!vis[i]) {
            for (int j = i * i; j < 100; j += i) {
                vis[j] = 1;
            }
        }
    }
    prime_num = 0;
    for (int i = 2; i < 100; i++) {
        if (!vis[i]) {
            prime[++prime_num] = i;
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    getAllPrime();
    while (scanf("%I64d", &n) != EOF) {
        long long ans = 0;
        for (int i = 2; i <= 64; i++) {
            int temp = i;
            int flag = 0;
            int num = 0;
            for (int j = 1; j <= prime_num; j++) {
                int c = 0;
                if (temp % prime[j] == 0) {
                    num++;
                    while (temp % prime[j] == 0) {
                        c++;
                        temp /= prime[j];
                    }
                }
                if (c > 1) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                continue;
            }
            double x = pow(n, 1.0 / i);
            if (sgn(x - 2.0) >= 0) {
                int cnt_num = x + eps;
                cnt_num--;
                if (num % 2) {
                    ans += cnt_num;
                }
                else {
                    ans -= cnt_num;
                }
            }
        }
        ans++;
        printf("%I64d\n", ans);
    }
}
