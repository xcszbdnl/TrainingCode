#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 1000007;
const long long MOD_NUMBER =  1000000007; 
long long value[MAX_NUMBER];
bool isGood[MAX_NUMBER * 9];

int a,b;
int length;

int check(int number) {
    while (number) {
        int temp = number % 10;
        if (temp != a && temp != b) {
            return 0;
        }
        number /= 10;
    }
    return 1;
}

long long getMod(long long number, long long power) {
    long long result = 1;
    long long square = number;
    while (power) {
        if (power & 1) {
            result = (result * square) % MOD_NUMBER;
        }
        square = (square * square) % MOD_NUMBER;
        power >>= 1;
    }
    return result;
}

int main() {

    scanf("%d%d%d", &a, &b, &length);
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    for (int s = 1; s <= length * a; s++) {
        if (check(s)) {
            isGood[s] = 1;
        }
    }
    value[0] = 1;
    for (long long i = 0; i < length; i++) {
        long long inverse = getMod(i + 1, MOD_NUMBER - 2);
        value[i + 1] = (value[i] * (length - i)) % MOD_NUMBER;
        value[i + 1] = (value[i + 1] * inverse) % MOD_NUMBER;
    }
    long long ans = 0;
    for (int s = 1; s <= length * a; s++) {
        if (isGood[s]) {
            int temp = s - length * b;
            if (temp >= 0 && (temp % (a - b)) == 0) {
                int x = temp / (a - b);
                ans = (ans + value[x]) % MOD_NUMBER;
            }
        }
    }
    cout << ans << endl;
}
