#include <stdio.h>
#include <string.h>

#define MOD_NUMBER 9901
#define MAX_NUMBER 10005

int prime[MAX_NUMBER];
int exp_number[MAX_NUMBER];

int getPowerMod(long long base, long long power) {
    int mod = 1;
    while (power) {
        if (power % 2) {
            mod = (mod * base) % MOD_NUMBER;
        }
        power >>= 1;
        base = (base * base) % MOD_NUMBER;
    }
    return mod;
}

int getSumMod(long long base, long long power) {
    if (power == 0) {
        return 1;
    }
    if (power % 2) {
        return (getSumMod(base, power / 2) * (1 + getPowerMod(base, power / 2 + 1))) % MOD_NUMBER;
    }
    else {
        return ((getSumMod(base, power / 2 - 1) * (1 + getPowerMod(base, power / 2))) + getPowerMod(base, power)) % MOD_NUMBER;
    }
}

    
int main() {

    int i;
    int A, B;
    int prime_number = 0;
    int ans;
    scanf("%d%d", &A, &B);
    for (i = 2; i * i <= A; i++) {
        if (A % i == 0) {
            prime[prime_number] = i;
            while ((A % i) == 0) {
                exp_number[prime_number]++;
                A /= i;
            }
            prime_number++;
        }
    }
    if (A != 1) {
        prime[prime_number] = A;
        exp_number[prime_number++] = 1;
    }
    ans = 1;
    for (i = 0; i < prime_number; i++) {
        ans = (ans * getSumMod(prime[i], B * exp_number[i])) % MOD_NUMBER;
    }
    printf("%d\n", ans);
}


