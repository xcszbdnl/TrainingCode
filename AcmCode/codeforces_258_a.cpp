#include <cstdio>
#include <cstring>

#define min(a,b) ((a) > (b)) ? (b) : (a)
const int maxn = 10007;

int main() {
//    freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    int ans = min(n, m);
    if (ans % 2 == 0) {
        printf("Malvika\n");
    }
    else {
        printf("Akshat\n");
    }
    return 0;
}
