#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100007;

int x_1, y_1, x_2, y_2;
int n;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d%d", &x_1, &y_1, &x_2, &y_2);
    if (x_1 == x_2) {
        if (y_1 < y_2) {
            swap(y_1, y_2);
        }
        int len = y_1 - y_2;
        printf("%d %d %d %d\n", x_1 + len, y_1, x_1 + len, y_2);
    }
    else if (y_1 == y_2) {
        if (x_1 < x_2) {
            swap(x_1, x_2);
        }
        int len = x_1 - x_2;
        printf("%d %d %d %d\n", x_1, y_1 + len, x_2, y_1 + len);
    }
    else {
        if (abs(x_1 - x_2) != abs(y_1 - y_2)) {
            printf("-1\n");
        }
        else {
            int len = abs(x_1 - x_2);
            if (x_1 < x_2) {
                swap(x_1, x_2);
                swap(y_1, y_2);
            }
            printf("%d %d %d %d\n", x_2, y_1, x_1, y_2);
        }
    }
    return 0;
}
