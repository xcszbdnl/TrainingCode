#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 65547;
int phi[MAX_NUMBER];

void getPhi() {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i < MAX_NUMBER; i++) {
        if (!phi[i]) {
            for (int j = i; j < MAX_NUMBER; j += i) {
                if (!phi[j]) {
                    phi[j] = j;
                }
                phi[j] = phi[j] * (i - 1) / i;
            }
        }
    }
}
int main() {

    getPhi();
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%d\n", phi[n - 1]);
    }
    return 0;
}
