#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int maxn = 200007;

int fa[maxn], pre[maxn];
vector<int> mod[maxn];

int findFa(int x) {
    if (x == fa[x]) {
        return x;
    }
    return fa[x] = findFa(fa[x]);
}
int main() {
//    freopen("in.txt", "r", stdin);
    int k;
    scanf("%d", &k);
    if (k == 1) {
        printf("3\n");
        return 0;
    }
    else if (k == 2) {
        printf("5\n");
        return 0;
    }
    for (int i = 0; i < 2 * k; i++) {
        fa[i] = i;
        mod[i].clear();
    }
    int ans = 0;
    for (int i = 1; i < 2 * k; i++) {
        long long temp = (long long)i *(long long)i;
        temp %= k;
        int cnt_mod = (k - temp);
        int flag = 0;
        while (cnt_mod < i) {
            int x = findFa(i);
            int y = findFa(cnt_mod);
            if (x != y) {
                fa[x] = y;
            }
            else {
                flag = 1;
                break;
            }
            pre[cnt_mod] = i;
            cnt_mod += k;
        }
        cnt_mod = (((k - i) % k) + k) % k;
        for (int j = 0; j < mod[cnt_mod].size(); j++) {
            int s = mod[cnt_mod][j];
            if (pre[s] == i) {
                continue;
            }
            int x = findFa(i);
            int y = findFa(s);
            if (x != y) {
                fa[x] = y;
            }
            else {
                flag = 1;
                break;
            }
        }
        if (flag) {
            ans = i;
            break;
        }
        temp = (long long)i * (long long)i;
        temp %= k;
        cnt_mod = temp;
        mod[cnt_mod].push_back(i);
    }
    printf("%d\n", ans);
    return 0;
}
