#include <cstdio>
#include <string.h>
#include <cmath>


const int MAX_NUMBER = 1000007;
char input[MAX_NUMBER];
int ans;
int n;

double log2(int a, int b) {
    return log10(b) / log10(a);
}

bool check(int power) {
    double left = log2(2, n) + power * log2(2, 10);
    double right = (log2(n + 1)) + power * log2(2, 10);
    if ((int)left != (int)right) {
        ans = (int)left + 1;
        return true;
    }
    return false;
}

int main() {

    while (scanf("%d", &n) != EOF) {
        sprintf(input, "%d", n);
        int flag;
        flag = 0;
        int length = strlen(input);
        for (int i = strlen(input) + 1; i < MAX_NUMBER; i++) {
            if (check(i)) {
                flag = 1;
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
