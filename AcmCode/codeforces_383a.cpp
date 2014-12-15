#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 200007;

int a[MAX_NUMBER];
int b[MAX_NUMBER];
int n;
int main() {

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    memset(b, 0, sizeof(b));
    for (int i = n; i >= 1; i--) {
        b[i] = b[i + 1] + a[i];
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            ans = ans + (n - i + 1 - b[i]);
        }
    }
    cout << ans << endl;
}
