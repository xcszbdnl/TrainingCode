#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 500007;

int value[MAX_NUMBER];
int vis[MAX_NUMBER];
int n;

void search(int cnt_number) {
    if (vis[cnt_number]) {
        return ;
    }
    vis[cnt_number] = 1;
    if (cnt_number % 2) {
        search(cnt_number / 2 + 1);
        value[cnt_number] = (value[cnt_number / 2 + 1] - 1) * 2;
    }
    else {
        search(cnt_number / 2);
        value[cnt_number] = value[cnt_number / 2] * 2;
    }
}
    

int main() {

    memset(vis, 0, sizeof(vis));
    value[1] = 1;
    vis[1] = 1;
    while (scanf("%d", &n) != EOF) {
        if (!n) {
            break;
        }
        search(n);
        printf("%d\n", value[n]);
    }
    return 0;
}
