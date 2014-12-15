#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;


#define MAX_NUMBER 35

long long numbers[MAX_NUMBER];

int main() {

    long long i;
    int pills;
    numbers[0] = 1;
    for (i = 1; i < MAX_NUMBER; i++) {
        numbers[i] = numbers[i - 1] * (4 * i - 2) / (i + 1);
    }
    while (scanf("%d", &pills) != EOF) {
        if (!pills) {
            break;
        }
        cout << numbers[pills] << endl;
    }
    return 0;
}
