#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

const int MAX_NUMBER = 1000;

int main() {
    freopen("input.txt", "w", stdout);
    srand(time(NULL));
    printf("%d\n", MAX_NUMBER);
    int i = 1;
    while (i <= MAX_NUMBER) {
        int temp_1 = (rand() % 70) + 1;
        int temp_2 = (rand() % 70) + 1;
        int temp_3 = (rand() % 70) + 1;
        printf("%d %d %d\n", temp_1, temp_2, temp_3);
        i++;
    }
    return 0;
}
