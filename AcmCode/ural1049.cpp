#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 10005;
const int MAX_PRIME = 10000;
bool vis[MAX_NUMBER];
int prime[MAX_PRIME];
int value[20];
int number[MAX_NUMBER];
int prime_number;

long long result;

void getAllPrime() {
    int m = sqrt(MAX_NUMBER + 0.5);
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= m; i++) {
        if (!vis[i]) {
            for (int j = i * i; j <= MAX_NUMBER; j += i) {
                vis[j] = 1;
            }
        }
    }
    prime_number = 0;
    for (int i = 2; i <= MAX_NUMBER; i++) {
        if (!vis[i]) {
            prime[++prime_number] = i;
        }
    }
}

int main() {

    getAllPrime();
    for (int i = 1; i <= 10; i++) {
        scanf("%d", &value[i]);
    }
    memset(number, 0, sizeof(number));
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= prime_number; j++) {
            if (value[i] % prime[j] == 0) {
                while (value[i] % prime[j] == 0) {
                    number[prime[j]]++;
                    value[i] /= prime[j];
                }
            }
        }
        if (value[i] != 1) {
            prime[value[i]]++;
        }
    }
    int ans = 1;
    for (int i = 1; i < MAX_NUMBER; i++) {
        ans = (ans * (number[i] + 1)) % 10;
    }
    printf("%d\n", ans % 10);
    return 0;
}
