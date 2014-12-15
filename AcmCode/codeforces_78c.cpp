#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

const double eps = 1e-10;
using namespace std;
long long n, m, k;

int main() {

    cin >> n >> m >> k;
    if (n % 2 == 0) {
        cout << "Marsel" << endl;
    }
    else {
        int flag = 0;
        long long temp = 1;
        if (m == 1 && k == 1) {
            cout << "Marsel" << endl;
            return 0;
        }
        for (long long i = 2; i <= sqrt(m) + 1; i++) {
            if (m % i == 0) {
                temp = m / i;
                break;
            }
        }
        if (temp >= k) {
            cout << "Timur" << endl;
        }
        else {
            cout << "Marsel" << endl;            
        }
    }
    return 0;
}
