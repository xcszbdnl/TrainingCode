#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 1007;

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
    sums[1] = 3;
    for (int i = 2; i < MAX_NUMBER; i++) {
        sums[i] = sums[i - 1] + 2 * phi[i];
    }
    int test_case;
    scanf("%d", &test_case);
    int case_number = 1;
    while (test_case--) {
        scanf("%d", &n);
        if (n == 0) {
            break;
        }
        cout << case_number << " " << n << " " << sums[n] << endl;
        case_number++;
    }
    return 0;
}
