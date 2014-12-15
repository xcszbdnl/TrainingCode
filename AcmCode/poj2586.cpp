#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    int s,d;
    int money[15];
    while (cin >> s >> d) {
        for (int i = 1; i < 13; i++) {
            money[i] = s;
        }
        money[5] = -d;
        money[10] = -d;
        for (int i = 0; i < 8; i++) {
            int current_minus = i + 5;
            while (1) {
                int sum = 0;
                for (int j = 1; j < 6; j++) {
                    sum += money[i + j];
                }
                if (sum > 0) {
                    money[current_minus] = -d;
                    current_minus--;
                }
                else {
                    break;
                }
            }
        }
        int sums = 0;
        for (int i = 1; i < 13; i++) {
            sums += money[i];
        }
        if (sums >= 0) {
            cout << sums << endl;
        }
        else {
            cout << "Deficit" << endl;
        }
    }
    return 0;
}
