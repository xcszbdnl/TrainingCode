#include <iostream>
#include <cstdio>

using namespace std;
int main() {
    freopen("input.txt", "r", stdin);
    double r, n;
    while (cin >> r >> n) {
        double ans = 1;
        for (int i = 0; i < n; i++) {
            ans = ans * r;
        }
        cout << ans << endl;
    }
    return 0;
}
