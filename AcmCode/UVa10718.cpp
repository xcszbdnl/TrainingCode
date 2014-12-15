#include <iostream>
#include <stdio.h>
using namespace std;
const int NUMBERS = 33;
int bit[NUMBERS];
int main() {
    freopen("input.txt","r",stdin);
    unsigned int N,L,U;
    while(cin >> N >> L >> U) {
        unsigned int  max_number = 0;
        unsigned int temp = 0;
        unsigned int ans;
        for (int i = 0; i < 32; i++) {
            bit[i] = (N >> i) & 1;
        }
        for (int i = 31; i >= 0; i--) {
            if (bit[i] == 0) {
                temp = max_number;
                temp = temp | (1 << i);
                if (temp <= U) {
                    max_number = temp;
                }
            } else {
                temp = max_number;
                temp = temp | (1 << i);
                if (temp <= L) {
                    max_number = temp;
                }
            }
        }
        cout << max_number << endl;
    }
    return 0;
}
