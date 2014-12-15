#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2007;
struct Candy {
    int height;
    int mass;
};


struct Candy one_candy[maxn], two_candy[maxn];
int n, init;
int one, two, ans, vis1[maxn], vis2[maxn];


int getAns(int cnt_type) {
    memset(vis1, 0, sizeof(vis1));
    memset(vis2, 0, sizeof(vis2));
    int result = 0;
    while (1) {
        int flag = 0;
        if (cnt_type == 1) {
            int index = -1;
            for (int i = 1; i <= one; i++) {
                if (!vis1[i] && one_candy[i].height <= init && (index == -1 || one_candy[index].mass < one_candy[i].mass)) {
                    index = i;
                }
            }
            if (index != -1) {
                vis1[index] = 1;
                init += one_candy[index].mass;
                flag = 1;
                result++;
                cnt_type = 2;
            }
        }
        else {
            int index = -1;
            for (int i = 1; i <= two; i++) {
                if (!vis2[i] && two_candy[i].height <= init && (index == -1 || two_candy[index].mass < two_candy[i].mass)) {
                    index = i;
                }
            }
            if (index != -1) {
                vis2[index] = 1;
                init += two_candy[index].mass;
                flag = 1;
                cnt_type = 1;
                result++;
            }
        }
        if (!flag) {
            break;
        }
    }
    return result;
}
int main() {
//    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &init);
    int cnt_type = 1;
    for (int i = 1; i <= n; i++) {
        int type;
        scanf("%d", &type);
        if (type) {
            two++;
            int a, b;
            scanf("%d%d", &a, &b);
            two_candy[two].height = a;
            two_candy[two].mass = b;
        }
        else {
            one++;
            int a, b;
            scanf("%d%d", &a, &b);
            one_candy[one].height = a;
            one_candy[one].mass = b;
        }
    }
    int temp = init;
    ans = getAns(1);
//    init = temp;
//    temp = getAns(2);
//    if (ans < temp) {
//        ans = temp;
//    }
    printf("%d\n", ans);
    return 0;
}
