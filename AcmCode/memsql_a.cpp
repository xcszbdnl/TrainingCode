#include <cstdio>
#include <cstring>

const int maxn = 100;

char name[][100] = {"vaporeon", "jolteon", "flareon", "espeon", "umbreon", "leafeon", "glaceon", "sylveon"};
char in[maxn];
int n;

int check(int cnt) {
    if (strlen(name[cnt]) != n) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (in[i] == '.') {
            continue;
        }
        else if (in[i] != name[cnt][i]){
            return 0;
        }
    }
    return 1;
}
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d%s", &n, in);
    int ans = 0;
    for (int i = 0; i < 8; i++) {
        if (check(i)) {
            ans = i;
            break;
        }
    }
    printf("%s\n", name[ans]);
    return 0;
}
