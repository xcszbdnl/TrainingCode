#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
#define min(a,b) ((a) > (b)) ? (b) : (a)
int n;
int x_1, y_1, x_2, y_2;

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d%d%d%d", &n, &x_1, &y_1, &x_2, &y_2);
    if (x_1 == 0) {
        int ans;
        if (x_2 == 0) {
            ans = abs(y_1 - y_2);
        }
        else if (x_2 == n) {
            int ans_1 = n - y_1 + n + n - y_2;
            int ans_2 = y_1 + n + y_2;
            ans = min(ans_1, ans_2);
        }
        else if (y_2 == 0) {
            ans = y_1 + x_2;
        }
        else if (y_2 == n) {
            ans = n - y_1 + x_2;
        }
        printf("%d\n", ans);
    }
    else if (x_1 == n) {
        int ans;
        if (x_2 == 0) {
            int ans_1 = n - y_1 + n + n - y_2;
            int ans_2 = y_1 + n + y_2;
            ans = min(ans_1, ans_2);
        }
        else if (x_2 == n) {
            ans = abs(y_1 - y_2);
        }
        else if (y_2 == 0) {
            ans = n - x_2 + y_1;
        }
        else if (y_2 == n) {
            ans = n - y_1 + n - x_2;
        }
        printf("%d\n", ans);
    }
    else if (y_1 == 0) {
        int ans;
        if (x_2 == 0) {
            ans = x_1 + y_2;
        }
        else if (x_2 == n) {
            ans = n - x_1 + y_2;
        }
        else if (y_2 == 0) {
            ans = abs(x_1 - x_2);
        }
        else if (y_2 == n) {
            int ans_1 = x_2 + n + x_1;
            int ans_2 = n - x_2 + n + n - x_1;
            ans = min(ans_1, ans_2);
        }
        printf("%d\n", ans);
    }
    else if (y_1 == n) {
        int ans;
        if (x_2 == 0) {
            ans = x_1 + n - y_2;
        }
        else if (x_2 == n) {
            ans = n - x_1 + n - y_2;
        }
        else if (y_2 == 0) {
            int ans_1 = x_1 + n + x_2;
            int ans_2 = n - x_1 + n + n - x_2;
            ans = min(ans_1, ans_2);
        }
        else if (y_2 == n) {
            ans = abs(x_1 - x_2);
        }
        printf("%d\n", ans);
    }
    return 0;
}
