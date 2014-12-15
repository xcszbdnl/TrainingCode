#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 1000006;

int rp[MAX_NUMBER];
int queue[MAX_NUMBER];

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        int total_number, tail, head, queue_length;
        total_number = tail = queue_length = 0;
        head = 1;
        char temp[10];
        scanf("%s", temp);
        while (1) {
            scanf("%s", temp);
            if (temp[0] == 'E') {
                break;
            }
            if (temp[0] == 'C') {
                int cnt_rp;
                scanf("%s", temp);
                scanf("%d", &rp[++total_number]);
                while (tail >= head && rp[queue[tail]] <= rp[total_number]) {
                    tail--;
                }
                queue[++tail] = total_number;
                queue_length++;
            }
            else if (temp[0] == 'G') {
                queue_length--;
            }
            else if (temp[0] == 'Q') {
                while (tail >= head && total_number - queue[head] + 1 > queue_length) {
                    head++;
                }
                if (head > tail) {
                    printf("-1\n");
                }
                else {
                    printf("%d\n", rp[queue[head]]);
                }
            }
        }
    }
    return 0;
}
