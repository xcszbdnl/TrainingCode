#include <cstdio>
#include <string.h>
#include <iostream>


using namespace std;

long  long value[1200];

int main() {


    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        long long n, p, t;
        scanf("%lld%lld%lld", &n, &t, &p);
        if (t < n * p) {
            cout << "0" << endl;
            continue;
        }
        memset(value, 0, sizeof(value));
        value[0] = 1;
        long long r = t - n * p;
        for (long long i = 0; i < r; i++) {
            value[i + 1] = (value[i] * (r + n - 1 - i) / (i + 1));
        }
        cout << value[r] << endl;
    }
    return 0;
}
