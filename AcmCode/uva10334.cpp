#include <cstdio>
#include <string.h>
#include <iostream>

using namespace std;
const int MAX_NUMBER = 1005;
long long value[MAX_NUMBER][5];

int main() {

    value[0][1] = value[0][2] = value[0][3] = value[0][4] = 1;    
    for (int i = 1; i < MAX_NUMBER; i++) {
        value[i][1] = value[i - 1][2] + value[i - 1][4];
        value[i][2] = value[i - 1][1];
        value[i][3] = value[i - 1][4];
        value[i][4] = value[i - 1][3] + value[i - 1][1];
    }
    int n;
    while (scanf("%d", &n) != EOF) {
        if (n == 0) {
            printf("1\n");
        }
        else {
            long long ans = value[n - 1][2] + value[n - 1][4];
            cout << ans << endl;
        }
    }
    return 0;
}
