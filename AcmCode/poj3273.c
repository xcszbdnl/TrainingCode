#include <stdio.h>

#define MAX_NUMBER 100005


int money[MAX_NUMBER];

int main() {

    int days, month;
    int highest, lower, mid, segment_number, month_money;
    int i;
    while (scanf("%d%d", &days, &month) != EOF) {
        highest = lower = 0;
        for (i = 1; i <= days; i++) {
            scanf("%d", &money[i]);
            highest += money[i];
            if (money[i] > lower) {
                lower = money[i];
            }
        }
        mid = (lower + highest) / 2;
        while (lower < highest) {
            segment_number = 1;
            month_money = 0;
            for (i = 1; i <= days; i++) {
                if (segment_number > month) {
                    break;
                }
                if (month_money + money[i] > mid) {
                    segment_number++;
                    month_money = 0;
                }
                month_money += money[i];
            }
            if (segment_number <= month) {
                highest = mid;
            }
            else {
                lower = mid + 1;
            }
            mid = (lower + highest) / 2;            
        }
        printf("%d\n", mid);
    }
    return 0;
}
