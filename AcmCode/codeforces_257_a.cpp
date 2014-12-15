#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
const int maxn = 1007;
struct Child {
    int order, val;
};

struct Child child[maxn];
queue<struct Child> que;
int n, m;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);
        child[i].val = a;
        child[i].order = i;
        que.push(child[i]);
    }
    int ans;
    while (!que.empty()) {
        struct Child cnt_child = que.front();
        if (que.size() == 1) {
            ans = cnt_child.order;
            break;
        }
        que.pop();
        cnt_child.val -= m;
        if (cnt_child.val > 0) {
            que.push(cnt_child);
        }
    }
    printf("%d\n", ans);
    return 0;
}
