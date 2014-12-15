#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 1000005
#define MAX_FOUR 250010

int semi_prime[MAX_FOUR];
int prime[MAX_FOUR];
int four_based[MAX_FOUR];
int vis[MAX_NUMBER];
int prime_number;

void getFourBased() {
    int i;
    for (i = 1; i < MAX_FOUR; i++) {
        four_based[i] = 4 * i + 1;
    }
}

void getPrime() {
    int flag, i, j;
    prime_number = 0;
    semi_prime[prime_number++] = 5;
    for (i = 2; i < MAX_FOUR && four_based[i] < MAX_FOUR; i++) {
        flag = 0;
        for (j = 0; semi_prime[j] * semi_prime[j] <= four_based[i]; j++) {
            if ((four_based[i] % semi_prime[j]) == 0) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            semi_prime[prime_number++] = four_based[i];
        }
    }
}

void getSemiPrime() {
    int i, j;
    int product;
    memset(vis, 0, sizeof(vis));
    for (i = 0; i < prime_number && semi_prime[i] < 1000; i++) {
        for (j = i; j < prime_number && semi_prime[j] < MAX_FOUR; j++) {
            product = semi_prime[i] * semi_prime[j];
            if (product < MAX_NUMBER && product > 0) {
                vis[product] = 1;
            }
        }
    }
}


int main() {

    int i;
    int h_number, semi_number;
    getFourBased();
    getPrime();
    getSemiPrime();
    while (scanf("%d", &h_number) != EOF) {
        if (!h_number) {
            break;
        }
        semi_number = 0;
        for (i = 5; i <= h_number; i += 4) {
            if (vis[i]) {
                semi_number++;
            }
        }
        printf("%d %d\n", h_number, semi_number);
    }
    return 0;
}
