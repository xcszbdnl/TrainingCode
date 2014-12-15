#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int maxn = 100007;


char s[maxn];
int start, len, loc;
vector<int> diff;
int turn(char a, char c) {
    if (a > c) {
        swap(a, c);
    }
    int num_1 = c - a;
    int num_2 = 'z' - c + a - 'a' + 1;
    return min(num_1, num_2);
}

int myabs(int x) {
    return x > 0 ? x : -x;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &len, &loc);
    scanf("%s", s);
    if (len == 1) {
        printf("0\n");
        return 0;
    }
    loc--;
    long long ans_1 = 0, ans_2 = 0, ans = 0;
    if (s[loc] != s[len - 1 - loc]) {
        ans_1 += turn(s[loc], s[len - 1 - loc]);
        ans_2 += turn(s[loc], s[len - 1 - loc]);
        s[loc] = s[len - 1 - loc];
    }
    if (loc <= len / 2 - 1) {
        for (int i = 0, j = len - 1; i <= j; i++, j--) {
            if (s[i] != s[j]) {
                diff.push_back(i);
            }
        }
        int temp = loc;
        for (int i = 0; i < diff.size(); i++) {
            ans_1 += myabs(diff[i] - loc);
            int another_loc = len - 1 - diff[i];
            ans_1 += turn(s[diff[i]], s[another_loc]);
            loc = diff[i];
        }
        loc = temp;
        for (int i = diff.size() - 1; i >= 0; i--) {
            ans_2 += myabs(diff[i] - loc);
            int another_loc = len - 1 - diff[i];
            ans_2 += turn(s[diff[i]], s[another_loc]);
            loc = diff[i];
        }
        ans = min(ans_1, ans_2);
        printf("%I64d\n", ans);
    }
    else {
        for (int i = 0, j = len - 1; i <= j; i++, j--) {
            if (s[i] != s[j]) {
                diff.push_back(j);
            }
        }
        int temp = loc;
        for (int i = 0; i < diff.size(); i++) {
            int x = diff[i];
            ans_1 += myabs(diff[i] - loc);
            int another_loc = len - 1 - diff[i];
            ans_1 += turn(s[diff[i]], s[another_loc]);
            loc = diff[i];
        }
        loc = temp;
        for (int i = diff.size() - 1; i >= 0; i--) {
            ans_2 += myabs(diff[i] - loc);
            int another_loc = len - 1 - diff[i];
            ans_2 += turn(s[diff[i]], s[another_loc]);
            loc = diff[i];
        }
        ans = min(ans_1, ans_2);
        printf("%I64d\n", ans);
    }
    return 0;
}
