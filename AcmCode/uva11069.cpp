#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 100;

long long value[MAX_NUMBER];
int vis[MAX_NUMBER];

void search(int cnt_number) {
    if (vis[cnt_number]) {
        return ;
    }
    vis[cnt_number] = 1;
    value[cnt_number] = 0;
    if (cnt_number > 2) {
        search(cnt_number - 2);
        value[cnt_number] += value[cnt_number - 2];
    }
    if (cnt_number > 3) {
        search(cnt_number - 3);
        value[cnt_number] += value[cnt_number - 3];
    }
}

int main() {

    memset(vis, 0, sizeof(vis));
    value[1] = 1;
    vis[1] = 1;
    value[2] = 1;
    vis[2] = 1;
    int n; 
    while (scanf("%d", &n) != EOF) {
        search(n);
        search(n - 1);
        long long ans = value[n] + value[n - 1];
        printf("%lld\n", ans);
    }
    return 0;
}
