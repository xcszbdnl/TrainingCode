#include <cstdio>
#include <iostream>

using namespace std;

long long n;

int main() {
    while (cin >> n) {
        if (n < 0) {
            break;
        }
        cout << 1 + n * (n + 1) / 2 << endl;
    }
    return 0;
}
