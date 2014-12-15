#include <stdio.h>
#include <string.h>

#define MAX_LENTH 1000006

char input[MAX_LENTH];
int next[MAX_LENTH];
int lenth;

void getNext() {
    int k, i;
    next[0] = -1;
    k = -1;
    for (i = 1; i < lenth; i++) {
        while (k != -1 && input[k + 1] != input[i]) {
            k = next[k];
        }
        if (input[k + 1] == input[i]) {
            k++;
        }
        next[i] = k;
    }
}


int main() {

    int period, one_string_lenth, i;
    int test_case = 1, flag = 1;
    while (scanf("%d", &lenth) != EOF) {
        if (!lenth) {
            break;
        }
        if (!flag) {
            printf("\n");
        }
        printf("Test case #%d\n", test_case);
        test_case++;
        scanf("%s", input);
        getNext();
        for (i = 1; i < lenth; i++) {
            one_string_lenth = i + 1 - (next[i] + 1);
            if ((i + 1) % one_string_lenth != 0) {
                continue;
            }
            period = (i + 1) / one_string_lenth;            
            if (period == 1) {
                continue;
            }
            else {
                printf("%d %d\n", i + 1, period);
            }
        }
        flag = 0;
    }
}
