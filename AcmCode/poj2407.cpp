#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
long long n, ans;

void getAns() {
    int m = sqrt(n + 0.5);
    ans = n;
    for (int i = 2; i <= m; i++) {
        if (n % i == 0) {
            ans = ans / i * (i - 1);
        }
        while (n % i == 0) {
            n /= i;
        }
    }
    if (n != 1) {
        ans = ans / n * (n - 1);
    }
}
int main() {

    while (cin >> n) {
        if (n == 0) {
            break;
        }
        getAns();
        cout << ans << endl;
    }
    return 0;
}
