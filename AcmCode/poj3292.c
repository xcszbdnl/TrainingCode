#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 1000002

int h_number[MAX_NUMBER];
int semi_prime_number[MAX_NUMBER];


void getSemiPrime() {
    int i, j;
    int product, count;
    memset(h_number, 0, sizeof(h_number));
    for (i = 5; i <= MAX_NUMBER; i += 4) {
        for (j = 5; j <= MAX_NUMBER; j += 4) {
            product = i * j;
            if (product > MAX_NUMBER) {
                break;
            }
            if (!h_number[i] && !h_number[j]) {
                h_number[product] = 1;
            }
            else {
                h_number[product] = -1;
            }
        }
    }
    count = 0;
    for (i = 1; i < MAX_NUMBER; i++) {
        if (h_number[i] == 1) {
            count++;
        }
        semi_prime_number[i] = count;
    }
}


int main() {

    int h;
    getSemiPrime();
    while (scanf("%d", &h) != EOF) {
        if (!h) {
            break;
        }
        printf("%d %d\n", h, semi_prime_number[h]);
    }
    return 0;
}
