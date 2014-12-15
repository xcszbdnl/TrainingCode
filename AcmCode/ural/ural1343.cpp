#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>
int n;
long long t;

bool isPrime(long long s) {
    for (int i = 2; i <= sqrt(s * 1.0); i++) {
        if (s % i == 0) {
            return false;
        }
    }
    return true;
}
int main() {
//    freopen("in.txt", "r", stdin);
    srand(time(NULL));
    scanf("%d", &n);
    if (n != 0) {
        scanf("%I64d", &t);
    }
    else {
        t = 0;
    }
    int flag = 0;
    while (!flag) {
        long long tmp = t;
        for (int i = n + 1; i <= 12; i++) {
            tmp = tmp * 10 + (rand() % 10);
        }
        if (isPrime(tmp)) {
            flag = 1;
            t = tmp;
            break;
        }
    }
    printf("%012I64d\n", t);
    return 0;
}
