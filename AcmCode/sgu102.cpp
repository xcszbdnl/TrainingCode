#include <cstdio>
#include <string.h>
#include <cmath>

const int MAX_NUMBER = 10006;


int phi[MAX_NUMBER];


void getAllPhi() {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i <= MAX_NUMBER; i++) {
        if (!phi[i]) {
            for (int j = i; j <= MAX_NUMBER; j += i) {
                if (!phi[j]) {
                    phi[j] = j;
                }
                phi[j] = phi[j] * (i - 1) / i;
            }
        }
    }
}

int main() {

    getAllPhi();
    int n;
    scanf("%d", &n);
    printf("%d\n", phi[n]);
    return 0;
    
}
