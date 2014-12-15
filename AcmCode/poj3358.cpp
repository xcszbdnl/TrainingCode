#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

const int MAX_NUMBER = 10006;

long long p, q, phi_q, ans, length;
long long factor[MAX_NUMBER], factor_number;
long long gcd(long long a, long long b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}

long long getMod(long long a, long long b) {
    long long ret = 1;
    long long cnt = a;
    while (b) {
        if (b & 1) {
            ret = (ret * cnt) % q;
        }
        cnt = (cnt * cnt) % q;
        b /= 2;
    }
    return ret;
}
long long getPhi() {
    long long temp = q;
    phi_q = q;
    for (long long i = 2; i * i < temp; i++) {
        if (temp % i == 0) {
            phi_q = phi_q / i * (i - 1);
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    if (temp != 1) {
        phi_q = phi_q / temp * (temp - 1);
    }
}

void getFactor() {
    factor_number = 0;
    for (long long i = 1; i * i < phi_q; i++) {
        if (phi_q % i == 0) {
            factor[++factor_number] = i;
            factor[++factor_number] = phi_q / i;
        }
    }
}
int main() {

    int case_number = 1;
    while (cin >> p) {
        getchar();
        cin >> q;
        long long com = gcd(p, q);
        p /= com;
        q /= com;
        p = p % q;
        int start_loc = 0;
        if (p == 0) {
            printf("Case #%d: 1,1\n", case_number);
            case_number++;
            continue;
        }
        while (q % 2 == 0) {
            start_loc++;
            q /= 2;
        }
        getPhi();
        getFactor();
        sort(factor + 1, factor + 1 + factor_number);
        length = 1;
        for (int i = 1; i <= factor_number; i++) {
            int mod = getMod(2, factor[i]);
            //printf("fa:%d ", factor[i]);
            if (mod == 1) {
                length = factor[i];
                break;
            }
        }
        cout << "Case #"<< case_number << ": " << start_loc + 1 << "," << length << endl;
        case_number++;
    }
    return 0;
}
