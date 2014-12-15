#include <cstdio>
#include <cstring>
const int MAX_NUMBER = 10007;
const int INF = 1000000007;
int value[MAX_NUMBER];
int total_number;
int m, k;

void getDivisor() {
    total_number = 0;
    for (int i = 2; i * i <= m; i++) {
        if (m % i == 0) {
            value[total_number++] = i;
            while (m % i == 0) {
                m /= i;
            }
        }
    }
    if (m != 1) {
        value[total_number++] = m;
    }
}

int check(int number) {
    int ans = 0;
    for (int i = 0; i < (1 << total_number); i++) {
        int cnt = 0;
        int temp = 0;
        int cnt_number = 1;
        for (int j = 0; j < total_number; j++) {
            if (i & (1 << j)) {
                cnt++;
                cnt_number *= value[j];
            }
        }
        temp = number / cnt_number;
        if (cnt % 2) {
            ans -= temp;
        }
        else {
            ans += temp;
        }
    }
    return ans;
}
int main() {
    //freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &m, &k) != EOF) {
        if (m == 1) {
            printf("%d\n", k);
            continue;
        }
        getDivisor();
        int ans;
        int low = 1;
        int high = INF;
        while (low <= high) {
            int mid = (low + high) >> 1;
            int order = check(mid);
            if (order >= k) {
                high = mid - 1;
                if (order == k) {
                    ans = mid;
                }
            }
            else {
                low = mid + 1;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
