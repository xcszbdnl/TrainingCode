#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    double m, n;
    while (cin >> m >> n) {
        double result = pow(n, 1/m);
        cout << result << endl;
    }
    return 0;
}
