#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 1000007;

long long phi[MAX_NUMBER];
long long sums[MAX_NUMBER];
int n;
void getPhi() {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for (int i = 2; i < MAX_NUMBER; i++) {
        if (!phi[i]) {
            for (int j = i; j < MAX_NUMBER; j += i) {
                if (!phi[j]) {
                    phi[j] = j;
                }
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}

int main() {

    getPhi();
    sums[1] = 0;
    for (int i = 2; i < MAX_NUMBER; i++) {
        sums[i] = sums[i - 1] + phi[i];
    }
    while (scanf("%d", &n) != EOF) {
        if (n == 0) {
            break;
        }
        cout << sums[n] << endl;
    }
    return 0;
}
