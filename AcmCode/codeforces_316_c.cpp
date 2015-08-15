#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 300007;
char s[maxn], q[maxn];
int f;
int n, m;
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    f = 0;
    for (int i = 0; i < n; i++) {
        int k = 0;
        int j = i;
        if (s[i] == '.') {
            for (; j < n && s[j] == '.'; j++) {
                k++;
            }
        }
        f += k == 0 ? 0 : k - 1;
        i = j;
    }
//    printf("first:%d\n", f);
    for (int i = 0; i < m; i++) {
        if (n == 1) {
            printf("0\n");
            continue;
        }
        int loc;
        scanf("%d%s", &loc, q);
        char c = q[0];
        loc--;
        if (c == s[loc]) {
            printf("%d\n", f);
            continue;
        }
        if (s[loc] != '.' && c != '.') {
            printf("%d\n", f);
            s[loc] = c;
            continue;
        }
        if (loc == 0) {
            if (c == '.') {
                if (s[1] == '.') {
                    f++;
                }
            }
            else {
                if (s[1] == '.') {
                    f--;
                }
            }
        }
        else if (loc == n - 1) {
            if (c == '.') {
                if (s[n - 2] == '.') {
                    f++;
                }
            }
            else {
                if (s[n - 2] == '.') {
                    f--;
                }
            }
        }
        else {
            if (c == '.') {
                if (s[loc - 1] == '.' && s[loc + 1] == '.') {
                    f += 2;
                }
                else if (s[loc - 1] == '.') {
                    f += 1;
                }
                else if (s[loc + 1] == '.') {
                    f += 1;
                }
            }
            else {
                if (s[loc - 1] == '.' && s[loc + 1] == '.') {
                    f -= 2;
                }
                else if (s[loc - 1] == '.') {
                    f -= 1;
                }
                else if (s[loc + 1] == '.'){
                    f -= 1;
                }
            }
        }
        s[loc] = c;
        printf("%d\n", f);
    }
    return 0;
}
