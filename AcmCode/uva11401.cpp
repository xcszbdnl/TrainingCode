#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 1000007;
long long ans[maxn];


int main() {
//    freopen("in.txt", "r", stdin);
    memset(ans, 0, sizeof(ans));
    for (long long i = 1; i < maxn; i++) {
        long long temp = ((i - 2 ) * (i - 1) / 2) - (i - 1 - i / 2);
        temp /= 2;
//        long long temp = ((i - 2) * (i - 1) / 2) - (i - 1) / 2;
//        temp /= 2;
//        cout << temp << endl;
        ans[i] = ans[i - 1] + temp;
    }
    int n;
    while (cin >> n) {
        if (n < 3) {
            break;
        }
        cout << ans[n] << endl;
    }
    return 0;
}
