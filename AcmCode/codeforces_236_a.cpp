#include <cstdio>
#include <cstring>

const int maxn = 10007;
int val[maxn];
int n, p;
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d%d", &n, &p);
        for (int i = 2; i <= n; i++) {
            printf("1 %d\n", i);
        }
        for (int i = 3; i <= n; i++) {
            printf("2 %d\n", i);
        }
        int num = n - 1 + n - 2;
        int temp = 2 * n + p - num;
        int cnt_n, cnt_loc;
        cnt_n = 3;
        cnt_loc = 4;
        while (temp) {
            printf("%d %d\n", cnt_n, cnt_loc);
            if (cnt_loc == n) {
                cnt_n++;
                cnt_loc = cnt_n + 1;
            }
            else {
                cnt_loc++;
            }
            temp--;
        }
    }
    return 0;
}
