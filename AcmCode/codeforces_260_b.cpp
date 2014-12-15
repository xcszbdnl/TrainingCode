#include <cstdio>
#include <cstring>

const int maxn = 1000007;

char in[maxn];

int getMod(int a, int b) {
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret = (ret * a) % 5;
        }
        a = (a * a) % 5;
        b /= 2;
    }
    return ret;
}

int getAns(int num) {
    int len = strlen(in);
    int ret = 1;
    for (int i = 0; i < len; i++) {
        ret = getMod(ret, 10);
        int cnt = in[i] - '0';
        ret = (ret * getMod(num, cnt)) % 5;
    }
    return ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%s", in);
    int ans = 1;
    ans = (ans + getAns(2)) % 5;
    ans = (ans + getAns(3)) % 5;
    ans = (ans + getAns(4)) % 5;
    ans = ((ans % 5) + 5) % 5;
    printf("%d\n", ans);
    return 0;
}
