#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1000006;

char in[maxn];

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%s", in);
    int len = strlen(in);
    int max_num = 1;
    for (int i = 0; i < len; i++) {
        if (in[i] >= '0' && in[i] <= '9') {
            max_num = max(max_num, in[i] - '0');
        }
        else {
            max_num = max(max_num, in[i] - 'A' + 10);
        }
    }
    int ret = 0;
    for (int k = max_num + 1; k <= 36; k++) {
        int ans = 0;
        for (int i = 0; i < len; i++) {
            int cnt_num;
            if (in[i] >= '0' && in[i] <= '9') {
                cnt_num = in[i] - '0';
            }
            else {
                cnt_num = in[i] - 'A' + 10;
            }
            ans = ((ans * k) + cnt_num) % (k - 1);
        }
        if (ans == 0) {
            ret = k;
            break;
        }
    }
    if (ret == 0) {
        printf("No solution.\n");
    }
    else {
        printf("%d\n", ret);
    }
    return 0;
}
