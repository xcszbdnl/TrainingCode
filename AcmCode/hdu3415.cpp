#include <cstdio>
#include <cstring>


const int MAX_NUMBER = 1000006;
const int INF = 2000000007;

int sums[2 * MAX_NUMBER];
int value[MAX_NUMBER];
int queue[2 * MAX_NUMBER];

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        int n, length, head, tail, max_number, max_length, start, end;
        scanf("%d%d", &n, &length);
        sums[0] = 0;
        head = tail = 1;
        queue[head] = 0;
        max_number = -INF;
        start = end = MAX_NUMBER;
        max_length = MAX_NUMBER;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &value[i]);
            sums[i] = sums[i - 1] + value[i];
        }
        for (int i = n + 1; i <= n + length - 1; i++) {
            sums[i] = sums[i - 1] + value[i % n];
        }
        for (int i = 1; i <= n + length - 1; i++) {
            while (tail >= head && i - queue[head] > length) {
                head++;
            }
            int temp = sums[i] - sums[queue[head]];
            if (temp >= max_number) {
                if (temp > max_number) {
                    max_number = temp;
                    max_length = i - queue[head];
                    start = queue[head] + 1;
                    end = i;
                }
                else {
                    if (queue[head] + 1 < start) {
                        max_length = i - queue[head];
                        start = queue[head] + 1;
                        end = i;
                    }
                    else if (queue[head] + 1 == start) {
                        if (max_length > i - queue[head]) {
                            max_length = i - queue[head];
                            start = queue[head] + 1;
                            end = i;
                        }
                    }
                }
            }
            while (tail >= head && sums[queue[tail]] > sums[i]) {
                tail--;
            }
            queue[++tail] = i;
        }
        if (end > n) {
            end -= n;
        }
        printf("%d %d %d\n", max_number, start, end);
    }
    return 0;
}
