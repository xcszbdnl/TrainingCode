#include <cmath>
#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 31269
#define MAX_PLACE 100

unsigned digit[MAX_NUMBER];
unsigned total_amount[MAX_NUMBER];
int integer[MAX_PLACE];

void getSize() {
    int i, place;
    memset(digit, 0, sizeof(digit));
    memset(total_amount, 0, sizeof(total_amount));
    digit[1] = total_amount[1] = 1;
    for (i = 2; i < MAX_NUMBER; i++) {
        place = (int)(log10((double) i)) + 1;
        digit[i] = digit[i - 1] + place;
        total_amount[i] = total_amount[i - 1] + digit[i];
    }
}

int getNumber(int location) {
    int i, group_location, number_location;
    int number, digit_number, power;
    for (i = 1; total_amount[i] < location; i++) {
        ;
    }
    group_location = location - total_amount[i - 1];
    for (i = 1; digit[i] < group_location; i++) {
        ;
    }
    number_location = group_location - digit[i - 1];
    number = i;
    digit_number = (int)log10((double)number) + 1;
    power = digit_number - number_location;
    for (i = 1; i <= power; i++) {
        number /= 10;
    }
    return number % 10;
}

int main() {

    int test_case, location;
    scanf("%d", &test_case);
    getSize();
    while (test_case--) {
        scanf("%d", &location);
        printf("%d\n", getNumber(location));
    }
    return 0;
}
