#include <stdio.h>
#include <string.h>


int cal(int order) {
    int number = 1;
    while (order != 1) {
        if ((order % 2) == 1) {
            order = order * 3 + 1;
        }
        else {
            order = order / 2;
        }
        number++;
    }
    return number;
}


int main() {

    int max_lenth, start, end, min, max, i, result, temp;
    while (scanf("%d%d", &start, &end) != EOF) {
        max_lenth = 0;
        min =start;
        max = end;
        if (min > max) {
            temp = min;
            min = max;
            max = temp;
        }
        for (i = min; i<= max; i++) {
            result = cal(i);
            if (result > max_lenth) {
                max_lenth = result;
            }
        }
        printf("%d %d %d\n", start, end, max_lenth);
    }
    return 0;
}
