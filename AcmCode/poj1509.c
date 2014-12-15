#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 10005
#define min(a,b) ((a) > (b))? (b) : (a)


char input[MAX_NUMBER];

int getMin() {
    int lenth = strlen(input);
    int i = 0, j = 1;
    int k, value;
    k = 0;
    while (i < lenth && j < lenth && k < lenth) {
        value = input[(i + k) % lenth] - input[(j + k) % lenth];
        if (!value)  {
            k++;
        }
        else if (value < 0) {
            j = j + k + 1;
            k = 0;
        }
        else {
            i = i + k + 1;
            k = 0;
        }
        if (i == j) {
            j++;
        }
    }
    return min(i, j);
}


int main() {

    int test_case;
    int min_number;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%s", input);
        min_number = getMin();
        printf("%d\n", min_number + 1);
    }
    return 0;
}

