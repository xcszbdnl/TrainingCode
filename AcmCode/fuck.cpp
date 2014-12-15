#include <cstdio>
#include <iostream>

using namespace std;

int main() {
    long long ans = 1;
    for (int i = 1; i <= 19; i++) {
        ans = ans * (19 - i + 1) / i;
        cout << ans << endl;
    }
    return 0;
}
