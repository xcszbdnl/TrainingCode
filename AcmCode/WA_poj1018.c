#include <stdio.h>
#include <cmath>

#define MAX_NUMBER 105
#define INF 1000000000

int dp[MAX_NUMBER];


int main() {

    int test_case;
    int i, j, minimum_band, device_number;
    int manufacture, bandwidth, price, chose_width, chose_price;
    double temp, best_device;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &device_number);
        dp[0] = 0;
        minimum_band = INF;
        for (i = 1; i <= device_number; i++) {
            scanf("%d", &manufacture);
            best_device = 0;
            for (j = 1; j <= manufacture; j++) {
                scanf("%d%d", &bandwidth, &price);
                if (bandwidth < minimum_band) {
                    temp = (double)bandwidth / (dp[i - 1] + price);
                }
                else {
                    temp = (double)minimum_band / (dp[i - 1] + price);
                }
                if (temp > best_device) {
                    chose_width = bandwidth;
                    chose_price = price;
                    best_device = temp;
                }
                else if (fabs(temp - best_device) < 1e-6 && bandwidth > chose_width) {
                    chose_width = bandwidth;
                    chose_price = price;
                    best_device = temp;
                }
            }
            if (chose_width < minimum_band) {
                minimum_band = chose_width;
            }
            dp[i] = dp[i - 1] + chose_price;
        }
        printf("%.3lf\n", best_device);
    }
    return 0;
}
