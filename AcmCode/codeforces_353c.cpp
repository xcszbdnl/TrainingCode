#include <cstdio>
#include <cstring>


const int MAX_NUMBER = 100006;

int value[MAX_NUMBER];
int sums[MAX_NUMBER];
int value_sums[MAX_NUMBER];
char m[MAX_NUMBER];

int sum_1, sum_2, sum_3;
int n, big_digit;
int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &value[i]);
    }
    big_digit = 0;
    sum_1 = sum_2 = sum_3 = 0;
    scanf("%s", m + 1);
    for (int i = 1; i <= n; i++) {
        if (m[i] == '1') {
            sum_1 += value[i];
            value_sums[i] = value_sums[i - 1] + value[i];
        }
        else {
            value_sums[i] = value_sums[i - 1];
        }
        sums[i] = sums[i - 1] + value[i];
    }
    for (int i = 1; i <= n; i++) {
        if (m[i] == '1') {
            int temp_sum = sums[i - 1] + value_sums[n] - value_sums[i];
            if (temp_sum > sum_1) {
                sum_1 = temp_sum;
            }
        }
    }
    printf("%d\n", sum_1);
    return 0;
}
