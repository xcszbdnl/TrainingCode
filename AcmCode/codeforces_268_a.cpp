#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;

int main() {
//    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    if (n <= 3) {
        printf("NO\n");
        return 0;
    }
    int num = 0;
    printf("YES\n");
    if (n % 2) {
        while (n > 5) {
            printf("%d - %d = 1\n", n, n - 1);
            n -= 2;
            num++;
        }
        printf("5 * 4 = 20\n");
        printf("20 + 3 = 23\n");
        printf("23 + 2 = 25\n");
        printf("25 - 1 = 24\n");
        for (int i = 1; i <= num; i++) {
            printf("1 * 24 = 24\n");
        }
    }
    else {
        num = 1;
        while (n > 4) {
            printf("%d - %d = 1\n", n, n - 1);
            n -= 2;
            num++;
        }
        printf("4 * 3 = 12\n");
        printf("12 * 2 = 24\n");
        for (int i = 1; i <= num; i++) {
            printf("1 * 24 = 24\n");
        }
    }
    return 0;
}
