#include <cstdio>
#include <cstring>

const int maxn = 100001;

short val[maxn];
short next[maxn], head[1001];
int n;
int main() {
//    freopen("in.txt", "r", stdin);
    memset(head, -1, sizeof(head));
    memset(next, -1, sizeof(next));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        char temp[10];
        scanf("%s", temp);
        if (temp[1] == 'U') {
            int a, b;
            scanf("%d%d", &a, &b);
            val[i] = b;
            next[i] = head[a];
            head[a] = i;
        }
        else {
            int a;
            scanf("%d", &a);
            printf("%d\n", val[head[a]]);
            head[a] = next[head[a]];
        }
    }
    return 0;
}
