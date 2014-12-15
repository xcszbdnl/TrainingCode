#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
long long n, k, d1, d2;

bool f1() {
    int flag = 0;
    long long temp = n - k - 2 * d1 - d2;
    if (temp < 0 || temp % 3 != 0) {
        flag = 1;
    }
    temp = k + 2 * d1 + d2;
    if (temp % 3 != 0) {
        flag = 1;
    }
    long long a = temp / 3;
    if (a - d1 < 0 || a - d1 - d2 < 0 || a > k) {
        flag = 1;
    }
    return !flag;
}

bool f2() {
    if (d1 < d2) {
        int flag = 0;
        long long temp = n - k - 2 * d2 + d1;
        if (temp < 0 || temp % 3 != 0) {
            flag = 1;
        }
        temp = k + 2 * d2 - d1;
        long long a3 = temp / 3;
        if (temp % 3 != 0 || a3 - d2 < 0 || a3 - d2 + d1 < 0 || a3 > k) {
            flag = 1;
        }
        return !flag;
    }
    else {
        int flag = 0;
        long long temp = n - k - 2 * d1 + d2;
        if (temp < 0 || temp % 3 != 0) {
            flag = 1;
        }
        temp = k + 2 * d1 - d2;
        long long a1 = temp / 3;
        if (temp % 3 != 0 || a1 - d1 < 0 || a1 - d1 + d2 < 0 || a1 > k) {
            flag = 1;
        }
        return !flag;
    }
}

bool f3() {
    int flag = 0;
    long long temp = n - k - d1 - d2;
    if (temp < 0 || temp % 3 != 0) {
        flag = 1;
    }
    temp = k + d1 + d2;
    long long a2 = temp / 3;
    if (temp % 3 != 0 || a2 - d1 < 0 || a2 - d2 < 0 || a2 > k) {
        flag = 1;
    }
    return !flag;
}

bool f4() {
    int flag = 0;
    long long temp = n - k - d1 - 2 *d2;
    if (temp < 0 || temp % 3 != 0) {
        flag = 1;
    }
    temp = k + d1 + 2 * d2;
    long long a3 = temp / 3;
    if (temp % 3 != 0 || a3 - d2 < 0 || a3 - d1 - d2 < 0 || a3 > k) {
        flag = 1;
    }
    return !flag;
}
int main() {
//    freopen("in.txt", "r", stdin);
    int test_case;
    cin >> test_case;
    while (test_case--) {
        cin >> n >> k >> d1 >> d2;
        int flag1, flag2, flag3, flag4;
        flag1 = f1();
        flag2 = f2();
        flag3 = f3();
        flag4 = f4();
        if (flag1 || flag2 || flag3 || flag4) {
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
    }
    return 0;
}
