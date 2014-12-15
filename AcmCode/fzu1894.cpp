#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 1000007;

int queue[MAX_NUMBER], rp[MAX_NUMBER];
int queue_length, cnt_number;

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        queue_length = cnt_number = 0;
        memset(queue, 0, sizeof(queue));
        memset(rp, 0, sizeof(rp));
        int front, rear;
        front = 1;
        rear = 0;
        char temp[10];
        scanf("%s", temp);
        while (1) {
            scanf("%s", temp);
            if (temp[0] == 'E') {
                break;
            }
            else if (temp[0] == 'C') {
                scanf("%s%d", temp, &rp[++cnt_number]);
                while (rear >= front && rp[queue[rear]] < rp[cnt_number]) {
                    rear--;
                }
                queue[++rear] = cnt_number;
                queue_length++;
            }
            else if (temp[0] == 'G') {
                queue_length--;
            }
            else if (temp[0] == 'Q') {
                while (rear >= front && queue[rear] - queue[front] + 1 > queue_length) {
                    front++;
                }
                if (rear < front) {
                    printf("-1\n");
                }
                else {
                    printf("%d\n", rp[queue[front]]);
                }
            }
        }
    }
    return 0;
}
