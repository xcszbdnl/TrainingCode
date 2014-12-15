#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const long long mod = 1000000007;
long long a, b;
int n;

struct Matrix {
    int a[4][4];
};

struct Matrix mul(struct Matrix a, struct Matrix b) {
    struct Matrix ret;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            ret.a[i][j] = 0;
            for (int k = 1; k<= 2; k++) {
                ret.a[i][j] += (a.a[i][k] * b.a[k][j]) % mod;
            }
        }
    }
    return ret;
};

int main() {
//    freopen("in.txt", "r", stdin);
    cin >> a >> b >> n;
    if (n == 1) {
        a = ((a % mod) + mod) % mod;
        cout << a << endl;
    }
    else if (n == 2) {
        b = ((b % mod) + mod) % mod;
        cout << b << endl;
    }
    else {
        n -= 2;
        struct Matrix result;
        result.a[1][1] = result.a[2][2] = 1;
        result.a[1][2] = result.a[2][1] = 0;
        struct Matrix cnt_mod;
        cnt_mod.a[1][1] = cnt_mod.a[2][1] = 1;
        cnt_mod.a[1][2] = -1;
        cnt_mod.a[2][2] = 0;
        while (n) {
            if (n % 2 == 1) {
                result = mul(result, cnt_mod);
            }
            cnt_mod = mul(cnt_mod, cnt_mod);
            n /= 2;
        }
        long long c = result.a[1][1] * b + result.a[1][2] * a;
        c = ((c % mod) + mod) % mod;
        cout << c << endl;
    }
    return 0;
}
