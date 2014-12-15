#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;
long long x, y, m;
long long g[100];
long long f[100];
int main() {

    cin >> x >> y >> m;
    if (x > y) {
        long long temp = x;
        x = y;
        y = temp;
    }
    if (y <= 0 && m > y) {
        cout << "-1" << endl;
        return 0;
    }
    if (m <= y) {
        cout << "0" << endl;
        return 0;
    }
    long long ans = 0;
    if (x < 0) {
        long long temp = -x;
        if (temp % y == 0) {
            x = 0;
            ans += temp / y;
        }
        else {
            x = (temp / y + 1) * y + x;
            ans += temp / y + 1;
        }
    }
    f[1] = 1;
    g[1] = 1;
    f[2] = 1;
    g[2] = 2;
    for (int i = 3; i <= 100; i++) {
        f[i] = f[i - 1] + f[i - 2];
        g[i] = g[i - 1] + g[i - 2];
    }
    for (int i = 1; i <= 100; i++) {
        if (f[i] * x + g[i] * y >= m) {
                ans += i;
                break;
        }
    }
    cout << ans << endl;
    return 0;
}
