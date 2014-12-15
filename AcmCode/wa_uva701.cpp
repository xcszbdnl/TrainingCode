#include <cmath>
#include <string.h>
#include <cstdio>

const int MAX_NUMBER = 100;


char input[MAX_NUMBER];
int digit;

bool check(long long temp) {
    char str_temp[20];
    int i = 0;
    int length = 0;
    while (temp) {
        str_temp[i] = temp % 10 + '0';
        temp /= 10;
        i++;
    }
    str_temp[i] = '\0';
    length = i;
    for (i = 0; input[i]; i++) {
        if (str_temp[length - i - 1] != input[i]) {
            return false;
        }
        temp /= 10;
    }
    return true;
}


int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%s", input) != EOF) {
        int ans;
        int flag = 0;
        for (int i = 0; i < 35; i++) {
            long long temp = 1ll << i;
            if (check(temp)) {
                flag = 1;
                ans = i;
                break;
            }
        }
        if (flag) {
            printf("%d\n", ans);
        }
        else {
            printf("no power of 2\n");
        }
    }
    return 0;
}
