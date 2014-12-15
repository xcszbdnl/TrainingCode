#include <cstdio>
#include <cstdlib>
#include <ctime>
int main() {
    freopen("in.txt", "w", stdout);
    srand(time(NULL));
    int n = 10;
    printf("%d\n", n);
    printf("%d\n", (rand() % n) + 1);
    for (int i = 1; i <= n; i++) {
        printf("%c", (rand() %26) + 'a');
    }
    return 0;
}
