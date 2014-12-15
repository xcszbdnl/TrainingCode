#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;
long long x, y, m;
long long g[100];
long long f[100];
int main() {
    freopen("in.txt", "r", stdin);
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
    while (1) {
        long long c = a + b;
        long long max_num = max(a, b);
        ans++;
        a = c;
        b = max_num;
    }
    cout << ans << endl;
}
