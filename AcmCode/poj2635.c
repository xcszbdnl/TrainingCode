#include <stdio.h>
#include <string.h>

#define MAX_PRIME 1000100
#define MAX_PRIME_NUMBER 1000000
#define MAX_LENTH 1010

int prime[MAX_PRIME_NUMBER];
int prime_number;
int minimum_size, product_lenth;
int product[MAX_LENTH];
char number[MAX_LENTH];

void getPrime() {
    int i, j;
    prime[prime_number++] = 2;
    for (i = 3; i <= MAX_PRIME; i++) {
        for (j = 0; prime[j] * prime[j] <= i; j++) {
            if ((i % prime[j]) == 0) {
                break;
            }
        }
        if (prime[j] * prime[j] > i) {
            prime[prime_number++] = i;
        }
    }
}

int getMod(int p) {
    int i, mod_number;
    mod_number = 0;
    for (i = product_lenth - 1; i >= 0; i--) {
        mod_number = (mod_number * 1000 + product[i]) % p;
    }
    return mod_number;
}



int main() {

    int i;
    int lenth, flag, location;
    getPrime();
    while (scanf("%s%d", number, &minimum_size) != EOF) {
        if (!strcmp(number, "0") && !minimum_size) {
            break;
        }
        memset(product , 0, sizeof(product));
        lenth = strlen(number);
        for (i = 0; i < lenth; i++) {
            location = (lenth + 2 - i) / 3 - 1;
            product[location] = product[location] * 10 + (number[i] - '0');
        }
        product_lenth = (lenth + 2) / 3;
        flag = 0;
        i = 0;
        while (prime[i] < minimum_size) {
            if (!getMod(prime[i])) {
                flag = 1;
                break;
            }
            i++;
        }
        if (flag) {
            printf("BAD %d\n", prime[i]);
        }
        else {
            printf("GOOD\n");
        }
    }
    return 0;
}

