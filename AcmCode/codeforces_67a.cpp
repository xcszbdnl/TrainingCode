#include <cstdio>
#include <cstring>

#define min(a,b) ((a) > (b)) ? (b) : (a)
#define max(a,b) ((a) > (b)) ? (a) : (b)
const int MAX_NUMBER = 1007;
const int INF = 1007 * 1007;
int sums[MAX_NUMBER], value[MAX_NUMBER], ans[MAX_NUMBER];
char input[MAX_NUMBER];
int n;
int main() {

    scanf("%d%s", &n, input + 1);
    int min_ans = INF;
    for (int i = 1; i <= n; i++) {
        ans[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        int left_max = 1;
        int right_max = 1;
        if (i <= n - 1 && (input[i] == 'L' || input[i] == '=')) {
            left_max = 1;
            for (int j = i; j <= n - 1; j++) {
                if (input[j] == 'L') {
                    left_max++;
                }
                else if (input[j] == 'R') {
                    break;
                }
            }
        }
        if (i >= 2 && (input[i - 1] == 'R' || input[i - 1] == '=')) {
            right_max = 1;
            for (int j = i - 1; j >= 1; j--) {
                if (input[j] == 'R') {
                    right_max++;
                }
                else if (input[j] == 'L') {
                    break;
                }
            }
        }
        ans[i] = max(left_max, right_max);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}
