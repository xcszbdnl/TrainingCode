#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10007;
int a, b;

int gcd(int x, int y) {
    if (y == 0) {
        return x;
    }
    return gcd(y, x % y);
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &a, &b);
    a = max(a, b);
    b = 0;
    for (int i = a; i <= 6; i++) {
        b++;
    }
    int com = gcd(6, b);
    printf("%d/%d\n", b / com, 6 / com);
    return 0;
}

