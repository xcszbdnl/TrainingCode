#include <cstdio>
#include <cstring>
#include <iostream>
int n, m;
using namespace std;
int main() {
    int test_case;
    cin >> test_case;
    while (test_case--) {
        cin >> n >> m;
        if ((n % (m + 1)) == 0) {
            cout << "Rabbit" << endl;
        }
        else {
            cout << "Grass" << endl;
        }
    }
}
