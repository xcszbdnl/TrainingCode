#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 20006;
const int INF = 100007;
int input[MAX_NUMBER];
int ans[MAX_NUMBER];
int n, m;

bool test(int number, int flag, int order, int pre) {
    for (int i = order; i <= order + m - 1; i++) {
        if ((pre + number * flag * (i - order + 1)) < input[i]) {
            return false;
        }
    }
    return true;
}

int getMin(int order, int pre) {
    int flag = -1;
    for (int i = order; i <= order + m - 1; i++) {
        if (input[i] > pre) {
            flag = 1;
            break;
        }
    }
    int low = 0;
    int high = INF;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (test(mid, flag, order, pre)) {
            if (flag == -1) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        else {
            if (flag == -1) {
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
    }
    if (flag == -1) {
        return -high;
    }
    else {
        return low;
    }
}

int main() {

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + m; i++) {
        scanf("%d", &input[i]);
    }
    int cnt_number = 0;
    for (int i = 1; i <= n; i++) {
        int min_x = getMin(i, cnt_number);
        cnt_number += min_x;
        ans[i] = min_x;
    }
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            printf("%d", ans[i]);
        }
        else {
            printf(" %d", ans[i]);
        }
    }
    printf("\n");
    return 0;
}
