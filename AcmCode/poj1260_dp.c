#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 105
#define INF 100000000

int categories[MAX_CATEGORIES];
int sums[MAX_CATEGORIES];
int price[MAX_CATEGORIES];
int minimal_money[MAX_CATEGORIES];

int main() {

    int test_case;
    int i ,j;
    int category_number, min_money, temp_money;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(minimal_money, 0, sizeof(minimal_money));
        scanf("%d", &category_number);
        for (i = 1; i <= category_number; i++) {
            scanf("%d%d", &sums[i], &price[i]);
            sums[i] += sums[i - 1]; 
        }
        for (i = 1; i <= category_number; i++) {
            min_money = INF;
            for (j = 0; j < i; j++) {
                temp_money = minimal_money[j] + (sums[i] - sums[j] + 10) * price[i];
                if (temp_money < min_money) {
                    min_money = temp_money;
                }
                minimal_money[i] = min_money;
            }
        }
        printf("%d\n", minimal_money[category_number]);
    }
}
