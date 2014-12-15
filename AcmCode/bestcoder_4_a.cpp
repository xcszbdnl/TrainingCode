#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1007;
int a[maxn];
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        for (int i = 1; i <= 6; i++) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + 1 + 6);
        int big = a[5] + a[6];
        int second = a[4] + a[3] + a[2];
        if (big > second) {
            printf("Grandpa Shawn is the Winner!\n");
        }
        else {
            printf("What a sad story!\n");
        }
    }
    return 0;
}
