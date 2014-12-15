#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <iostream>
const int maxn = 50007;

using namespace std;
struct Par {
    int loc, val;
    bool operator < (const struct Par &a) const {
        return val > a.val;
    }
};

struct Par par[maxn];
priority_queue<struct Par> que;
char input[maxn];
int length, num, vis[maxn];
int main() {
//    freopen("input.txt", "r", stdin);
    memset(vis, 0, sizeof(vis));
    scanf("%s", input);
    length = strlen(input);
    num = 0;
    long long ans = 0;
    for (int i = 0; i < length; i++) {
        if (input[i] == '?') {
            num++;
            int a, b;
            scanf("%d%d", &a, &b);
            input[i] = ')';
            vis[i] = 1;
            ans += b;
            par[i].loc = i;
            par[i].val = a - b;
        }
    }
    int top = 0;
//    printf("%d\n", ans);
//    printf("%s\n", input);
//    printf("1:%d %d\n", par[1].loc, par[1].val);
//    printf("2:%d %d\n", par[2].loc, par[2].val);
    for (int i = 0; i < length; i++) {
        if (input[i] == '(') {
            top++;
        }
        else {
            top--;
            if (vis[i] == 1) {
                que.push(par[i]);
            }
            if (top < 0) {
                if (que.empty()) {
                    break;
                }
                else {
                    struct Par cnt = que.top();
                    que.pop();
                    input[cnt.loc] = '(';
                    ans += cnt.val;
                }
                top += 2;
            }
        }
    }
    if (top != 0) {
        printf("-1\n");
    }
    else {
        cout << ans << endl;
        printf("%s\n", input);
    }
}
