#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;
long long n, k;

map<long long, int> maps;

const long long mod = 1000 * 1000 * 1000 + 7;
long long getPhi(long long cnt) {
    int m = (int)sqrt(cnt + 0.5);
    int ans = cnt;
    for (int i = 2; i <= m; i++) {
        if (cnt % i == 0) {
            ans = ans / i * (i - 1);
            while(cnt % i == 0) {
                cnt /= i;
            }
        }
    }
    if (cnt > 1) {
        ans = ans / cnt * (cnt - 1);
    }
    return ans;
}
int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%I64d%I64d", &n, &k) != EOF) {
        if (n == 1) {
            printf("1\n");
            continue;
        }
        if (k > 2) {
            printf("0\n");
            continue;
        }
        if (k == 2) {
            printf("1\n");
            continue;
        }
        else {
            long long result = 0;
            int m = (int)sqrt(n + 0.5);
            long long temp_1, temp_2;
            temp_1 = getPhi(n);
            temp_1 = (temp_1 * 2) % mod;
            result = temp_1;
            for (int i = 2; i <= m; i++) {
                if (n % i == 0) {
                    temp_1 = getPhi(n / i);
                    temp_2 = getPhi(i);
                    temp_1 = (temp_1 * temp_2) % mod;
                    if (i == n / i) {
                        result = (result + temp_1) % mod;
                    }
                    else {
                        temp_1 = (temp_1 * 2) % mod;
                        result = (result + temp_1) % mod;
                    }
                }
            }
            printf("%I64d\n", result);
        }
    }
    return 0;
}
