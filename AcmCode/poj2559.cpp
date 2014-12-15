#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_NUMBER = 100007;

long long value[MAX_NUMBER];

int left_loc[MAX_NUMBER];
int right_loc[MAX_NUMBER];
int n;

int main() {

    while (scanf("%d", &n) != EOF) {
        if (!n) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            scanf("%I64d", &value[i]);
        }
        left_loc[1] = 1;
        for (int i = 2; i <= n; i++) {
            int j = i;
            while (j != 1 && value[j - 1] >= value[i]) {
                j = left_loc[j - 1];
            }
            left_loc[i] = j;
        }
        right_loc[n] = n;
        for (int i = n - 1; i >= 1; i--) {
            int j = i;
            while (j != n && value[j + 1] >= value[i]) {
                j = right_loc[j + 1];
            }
            right_loc[i] = j;
        }
        long long max_number = 0;
        for (int i = 1; i <= n; i++) {
            long long temp = (right_loc[i] - left_loc[i] + 1) * value[i];
            if (temp > max_number) {
                max_number = temp;
            }
        }
        cout << max_number << endl;
    }
    return 0;
}
