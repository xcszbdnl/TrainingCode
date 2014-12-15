#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_NUMBER 60

unsigned long long number[MAX_NUMBER][MAX_NUMBER];
char pins[MAX_NUMBER][MAX_NUMBER];

long long gcd(unsigned long long a, unsigned long long b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}


int main() {

    int rows, location, i, j;
    unsigned long long total_number, divisor, ball_number;
    scanf("%d%d", &rows, &location);
    total_number = 1LL << rows;
    number[1][0] = total_number;
    for (i = 1; i <= rows; i++) {
        for (j = 0; j < i; j++) {
            cin >> pins[i][j];
        }
    }
    for (i = 1; i <= rows; i++) {
        for (j = 0; j < i; j++) {
            if (pins[i][j] == '*') {
                number[i + 1][j] += number[i][j] >> 1;
                number[i + 1][j + 1] += number[i][j] >> 1;
            }
            else {
                number[i + 2][j + 1] += number[i][j];
            }
        }
    }
    ball_number = number[rows + 1][location];
    divisor = gcd(ball_number, total_number);
    printf("%lld/%lld\n", ball_number / divisor, total_number / divisor);
    return 0;
}
