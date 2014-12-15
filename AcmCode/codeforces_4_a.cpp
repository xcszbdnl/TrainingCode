#include <cstdio>
#include <cstring>

int main() {
    int w;
    scanf("%d", &w);
    if (w == 2 || w % 2 == 1) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
    }
    return 0;
}
