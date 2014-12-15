#include <stdio.h>
#include <string.h>

#define MAX_LENTH 100
#define MAX_STEP 15

int count[MAX_STEP];
char digit[MAX_STEP][MAX_LENTH];

void getInventory(int number) {
    int i;
    int lenth = 0;
    memset(count, 0, sizeof(count));
    for (i = 0; digit[number - 1][i]; i++) {
        count[digit[number - 1][i] - '0']++;
    }
    for (i = 0; i <= 9; i++) {
        if (count[i] != 0) {
            if (count[i] >= 10) {
                digit[number][lenth++] = count[i] / 10 + '0';
            }
            digit[number][lenth++] = count[i] % 10 + '0';
            digit[number][lenth++] = i + '0';
        }
    }
    digit[number][lenth] = '\0';
}

void solve() {
    int i, j, flag;
    int original_number, source, step;
    flag = 0;
    for (i = 1; i <= MAX_STEP && !flag; i++) {
        getInventory(i);
        for (j = 0; j < i; j++) {
            if (strcmp(digit[i], digit[j]) == 0) {
                flag = 1;
                source = i;
                original_number = j;
                break;
            }
        }
    }
    if (flag) {
        if (source - original_number == 1) {
            if (original_number == 0) {
                printf("%s is self-inventorying\n", digit[0]);
            }
            else {
                printf("%s is self-inventorying after %d steps\n", digit[0], original_number);
            }
        }
        else {
            printf("%s enters an inventory loop of length %d\n", digit[0], source - original_number);            
        }
    }
    else {
        printf("%s can not be classified after 15 iterations\n", digit[0]);
    }
    return ;
}



int main() {

    while (scanf("%s", digit[0]) != EOF) {
        if (strcmp("-1", digit[0]) == 0) {
            break;
        }
        solve();
    }
    return 0;
}
