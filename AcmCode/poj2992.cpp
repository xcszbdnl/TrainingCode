#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 1007;

unsigned long long f[MAX_NUMBER][MAX_NUMBER];
long long ans;
int vis[MAX_NUMBER];
int prime[MAX_NUMBER];
int prime_number;

void getPrime() {
    for (int i = 2; i <= sqrt(MAX_NUMBER + 0.5); i++) {
        if (!vis[i]) {
            for (int j = 2 * i; j < MAX_NUMBER; j += i) {
                vis[j] = 1;
            }
        }
    }
    prime_number = 0;
    for (int i = 2; i < MAX_NUMBER; i++) {
        if (!vis[i]) {
            prime[++prime_number] = i;
        }
    }
}

void getAns() {
    memset(f, 0, sizeof(f));
    for (int i = 2; i < 433; i++) {
        for (int j = 1; j <= prime_number; j++) {
            int cnt_number = i;
            while (cnt_number) {
                f[i][j] += cnt_number / prime[j];
                cnt_number /= prime[j];
            }
        }
    }
}

int main() {

    int n, k;
    getPrime();
    getAns();
    while (scanf("%d%d", &n, &k) != EOF) {
        ans = 1;
        for (int i = 1; i <= prime_number; i++) {
            long long ans_1 = f[n][i];
            long long ans_2 = f[n - k][i];
            long long ans_3 = f[k][i];
            ans_1 = ans_1 - ans_2 - ans_3;
            ans = ans * (ans_1 + 1);
        }
        cout << ans << endl;
    }
    return 0;
}
