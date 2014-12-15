#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAX_NUMBER 10005


struct Product {
    int price;
    int deadline;
};

struct Product product[MAX_NUMBER];
int vis[MAX_NUMBER];

bool cmp(struct Product a, struct Product b) {
    return a.price > b.price;
}


int main() {

    int product_number;
    int i, j, previous_deadline, max_money, total_money, sell_date;
    while (scanf("%d", &product_number) != EOF) {
        memset(product, 0, sizeof(product));
        memset(vis, 0, sizeof(vis));
        total_money = 0;
        for (i = 0; i < product_number; i++) {
            scanf("%d%d", &product[i].price, &product[i].deadline);
        }
        sort(product, product + product_number, cmp);
        for (i = 0; i < product_number; i++) {
            sell_date = product[i].deadline;
            while (sell_date > 0 && vis[sell_date]) {
                sell_date--;
            }
            if (sell_date > 0) {
                vis[sell_date] = 1;
                total_money += product[i].price;
            }
        }
        printf("%d\n", total_money);
    }
    return 0;
}
