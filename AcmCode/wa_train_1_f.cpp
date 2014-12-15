#include <cstdio>
#include <string.h>


const int MAX_NUMBER = 2005;

int input[MAX_NUMBER], temp[MAX_NUMBER];
int number, increase_cost, decrease_cost;

int main() {

    scanf("%d", &number);
    for (int i = 1; i <= number; i++) {
        scanf("%d", &input[i]);
    }
    memcpy(temp, input, sizeof(input));
    increase_cost = 0;
    for (int i = 2; i <= number; i++) {
        if (input[i] < temp[i - 1]) {
            increase_cost = increase_cost + temp[i - 1] - input[i];
            temp[i] = temp[i - 1];
        }
        else {
            temp[i] = input[i];
        }
    }
    memcpy(temp, input, sizeof(input));
    decrease_cost = 0;
    for (int i = 2; i <= number; i++) {
        if (input[i] > temp[i - 1]) {
            decrease_cost = decrease_cost + input[i] - temp[i - 1];
            temp[i] = temp[i - 1];
        }
        else {
            temp[i] = input[i];
        }
    }
    int min_cost;
    if (decrease_cost > increase_cost) {
        min_cost = increase_cost;
    }
    else {
        min_cost = decrease_cost;
    }
    printf("%d\n", min_cost);
    return 0;
}

    
