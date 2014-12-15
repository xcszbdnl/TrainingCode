#include <cstdio>
#include <cstring>
#include <iostream>

#define max(a,b) ((a) > (b)) ? (a) : (b)
using namespace std;

long long n, m, k;

int main() {
    freopen("in.txt", "r", stdin);
    long long ans = 0;
    cin >> n >> m >> k;
    if (k > n + m - 2) {
        cout << - 1 << endl;
        return 0;
    }
    if (k <= n - 1) {
        long long temp = m * (n / (k + 1));
        ans = max(ans, temp);
    }
    if (k <= m - 1) {
        long long temp = (m / (k + 1)) * n;
        ans = max(ans, temp);
    }
    if (n - 1 >= k / 2 && m - 1 >= k / 2) {
        if (k % 2 == 0) {
            long long temp = n * m / (k * k / 4 + k + 1);
            ans = max(ans, temp);
        }
        else {
            long long ans_1 = k / 2 + 1;
            long long temp_1 = -(ans_1 * ans_1) + k * ans_1 + k + 1;
            if (temp_1 != 0) {
                temp_1 = n * m / temp_1;
                ans = max(ans, temp_1);
            }
            long long ans_2 = k / 2;
            long long temp_2 = -(ans_2 * ans_2) + k * ans_2 + k + 1;
            if (temp_2 != 0) {
                temp_2 = n * m / temp_2;
                ans = max(ans, temp_2);
            }
        }
        cout << ans << endl;
    }
}
