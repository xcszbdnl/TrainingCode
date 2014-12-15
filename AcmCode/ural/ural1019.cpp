#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1000007;
const int MAXLEN = 1000000000;
struct Re {
    int left, right, type;
};

struct Re re[maxn];
int num[maxn], n, len, m, val[maxn], max_len, ans_1, ans_2;

void init() {
    sort(num + 1, num + 1 + m);
    len = 1;
    for (int i = 2; i <= m; i++) {
        if (num[i] != num[i - 1]) {
            len++;
            num[len] = num[i];
        }
    }
}

int biSearch(int number) {
    int low = 1;
    int high = len;
    while (low <= high) {
        int mid = (low + high) >> 1;
        if (num[mid] == number) {
            return mid;
        }
        else if (num[mid] > number) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    return 1;
}
int main() {
    freopen("in.txt", "r", stdin);
    m = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        char c;
        scanf("%d%d %c", &a, &b, &c);
        num[++m] = a;
        num[++m] = b;
        re[i].left = a;
        re[i].right = b;
        re[i].type = c == 'b';
    }
//    for (int i = 1; i <= m; i++) {
//        printf("%d ", num[i]);
//    }
    init();
//    printf("len::%d\n", len);
    memset(val, 0, sizeof(val));
    for (int i = 1; i <= n; i++) {
        int left = biSearch(re[i].left);
        int right = biSearch(re[i].right);
        for (int j = left + 1; j <= right; j++) {
            val[j] = re[i].type;
        }
//        printf("%d--->%d\n", left, right);
    }
    int head = 1;
    max_len = num[1];
    ans_1 = 0;
    ans_2 = num[1];
//    for (int i = 1; i <= len; i++) {
//        printf("%d ", val[i]);
//    }
    val[len + 1] = 0;
    num[len + 1] = MAXLEN;
    val[len + 2] = 1;
    while (head <= len) {
        while (val[head] == 1 && head <= len) {
            head++;
        }
        int i;
        for (i = head + 1; i <= len + 2; i++) {
            if (val[i] != val[head]) {
                int temp = num[i - 1] - num[head - 1];
                if (temp > max_len) {
                    max_len = temp;
                    ans_1 = head - 1;
                    ans_2 = i - 1;
                }
                break;
            }
        }
        head = i;
    }
    printf("%d %d\n", num[ans_1], num[ans_2]);
    return 0;
}
