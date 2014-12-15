#include <cstdio>
#include <string.h>

#define MAX_NUMBER (250 * 250)

int string_1[MAX_NUMBER];
int string_2[MAX_NUMBER];
int dp[MAX_NUMBER];
int stack[MAX_NUMBER];


int main() {

    int test_case;
    int case_number = 1;
    scanf("%d", &test_case);
    while (test_case--) {
        int n, length_1, length_2;
        memset(dp, 0, sizeof(dp));
        memset(string_1, 0, sizeof(string_1));
        memset(string_2, 0, sizeof(string_2));
        scanf("%d%d%d", &n, &length_1, &length_2);
        for (int i = 1; i <= length_1 + 1; i++) {
            int temp;
            scanf("%d", &temp);
            string_1[temp] = i;
        }
        for (int i = 1; i <= length_2 + 1; i++) {
            int temp;
            scanf("%d", &temp);
            if (string_1[temp]) {
                string_2[i] = string_1[temp];
            }
        }
        int top = 0;
        stack[top] = -1;
        int max_number = 0;
        for (int i = 1; i <= length_2 + 1; i++) {
            if (string_2[i] > stack[top]) {
                stack[++top] = string_2[i];
            }
            else {
                int high = top;
                int low = 1;
                while (low <= high) {
                    int mid = (low + high) >> 1;
                    if (stack[mid] < string_2[i]) {
                        low = mid + 1;
                    }
                    else {
                        high = mid - 1;
                    }
                }
                stack[low] = string_2[i];
            }
            dp[i] = top;
            if (max_number < dp[i]) {
                max_number = dp[i];
            }
        }
        printf("Case %d: %d\n", case_number, max_number);
        case_number++;
    }
    return 0;
}
