#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;

const int maxn = 100007;
const int INF = 1000000007;
int n;
int a[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int flag = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i] < a[i - 1]) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        printf("yes\n");
        printf("1 1\n");
        return 0;
    }
    flag = 0;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] < a[i + 1]) {
            flag = 1;
            break;
        }
    }
    if (!flag) {
        printf("yes\n");
        printf("1 %d\n", n);
        return 0;
    }
    int loc_1;
    for (int i = 1; i <= n; i++) {
        if (i + 1 <= n && a[i] > a[i + 1]) {
            loc_1 = i;
            break;
        }
    }
    int loc_2;
    a[n + 1] = INF;
    for (int i = loc_1; i <= n; i++) {
        if (a[i] < a[i + 1]) {
            loc_2 = i;
            break;
        }
    }
    for (int i = loc_1, j = loc_2; i <= j; i++, j--) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    flag = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i] < a[i - 1]) {
            flag = 1;
            break;
        }
    }
    if (flag) {
        printf("no\n");
    }
    else {
        printf("yes\n");
        printf("%d %d\n", loc_1, loc_2);
    }
    return 0;
}
