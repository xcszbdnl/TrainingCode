#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1007;
int a[4];
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d%d%d", &a[0], &a[1], &a[2], &a[3]);
    sort(a, a + 4);
    if (a[2] < a[0] + a[1]) {
        printf("TRIANGLE\n");
    }
    else if (a[1] + a[2] > a[3]) {
        printf("TRIANGLE\n");
    }
    else if (a[0] + a[1] == a[2] || a[1] + a[2] == a[3]) {
            printf("SEGMENT\n");
    }
    else {
        printf("IMPOSSIBLE\n");
    }
    return 0;
}
