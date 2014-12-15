#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

const int maxn = 400007;
struct Loc {
    int x;
};

struct Loc loc[maxn];
int n, m, vis[maxn], prime[maxn], prime_num, d[maxn], len, val[maxn];
int modify;


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

long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
long long getAns(int a, int b, int p) {
    long long tot = (long long)(a + b) * (b - a + 1) / 2;
    len = 0;
    int temp = p;
    for (int i = 1; i <= prime_num && prime[i] * prime[i] <= temp; i++) {
        if (temp % prime[i] == 0) {
            d[len++] = prime[i];
            while (temp % prime[i] == 0) {
                temp /= prime[i];
            }
        }
    }
    if (temp != 1) {
        d[len++] = temp;
    }
    for (int i = 1; i < (1 << len); i++) {
        int c = 0;
        long long cnt_num = 1;
        for (int j = 0; j < len; j++) {
            if ((1 << j) & i) {
                c++;
                cnt_num *= d[j];
            }
        }
        long long sum_1 = 0, sum_2 = 0;
        sum_1 = cnt_num * (long long)(1 + b / cnt_num) * (b / cnt_num) / 2;
        sum_2 = cnt_num * (long long)(1 + (a - 1) / cnt_num) * ((a - 1) / cnt_num) / 2;
        sum_1 -= sum_2;
        if (c % 2) {
            tot -= sum_1;
        }
        else {
            tot += sum_1;
        }
    }
    return tot;
}

int main() {
//    freopen("in.txt", "r", stdin);
    getAllPrime();
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
//        maps.clear();
        modify = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            val[i] = i;
        }
        for (int i = 1; i <= m; i++) {
            int a;
            scanf("%d", &a);
            if (a == 1) {
                int x, y, p;
                scanf("%d%d%d", &x, &y, &p);
                long long ans = getAns(x, y, p);
                for (int j = 0; j < modify; j++) {
                    int c = loc[j].x;
                    if (c < x || c > y) {
                        continue;
                    }
                    int com = gcd(c, p);
                    if (com == 1) {
                        ans -= c;
                        com = gcd(val[c], p);
                        if (com == 1) {
                            ans += val[c];
                        }
                    }
                    else {
                        com = gcd(val[c], p);
                        if (com == 1) {
                            ans += val[c];
                        }
                    }
                }
                printf("%I64d\n", ans);
            }
            else {
                int x, c;
                scanf("%d%d", &x, &c);
                int flag = 0;
                for (int j = 0; j < modify; j++) {
                    if (loc[j].x == x) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    loc[modify++].x = x;
                }
                val[x] = c;
            }
        }
    }
    return 0;
}

