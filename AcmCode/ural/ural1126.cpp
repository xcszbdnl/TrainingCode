#include <cstdio>
#include <cstring>

const int maxn = 30000;

int val[maxn], que[maxn];
int m;

int main() {
//    freopen("in.txt", "r", stdin);
    int cnt_num = 0;
    scanf("%d", &m);
    while (scanf("%d", &val[++cnt_num]) != EOF) {
        if (val[cnt_num] == -1) {
            cnt_num--;
            break;
        }
    }
    int front = 0;
    int rear = -1;
    for (int i = 1; i <= cnt_num; i++) {
        while (rear >= front && val[que[rear]] < val[i]) {
            rear--;
        }
        rear++;
        que[rear] = i;
        if (i >= m) {
            while (rear >= front && i - que[front] + 1 > m) {
                front++;
            }
            printf("%d\n", val[que[front]]);
        }
    }
    return 0;
}
