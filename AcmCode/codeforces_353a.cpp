#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 105;

struct Point {
    int upper, lower;
};

struct Point point[MAX_NUMBER];
int n;

int main() {

    scanf("%d", &n);
    int upper_sum, lower_sum;
    upper_sum = lower_sum = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &point[i].upper, &point[i].lower);
        upper_sum += point[i].upper;
        lower_sum += point[i].lower;
    }
    if (upper_sum % 2 == 0 && lower_sum % 2 == 0) {
        printf("0\n");
    }
    else if (upper_sum % 2 == 1 && lower_sum % 2 == 1) {
        int flag = 0;
        for (int i = 1; i <= n; i++) {
            if ((point[i].upper % 2 == 0 && point[i].lower % 2 == 1) || (point[i].upper % 2 == 1 && point[i].lower % 2 == 0)) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            printf("1\n");
        }
        else {
            printf("-1\n");
        }
    }
    else {
        printf("-1\n");
    }
    return 0;
}
