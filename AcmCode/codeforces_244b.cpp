#include <cstdio>
#include <cstring>
#include <algorithm>


using namespace std;
const int MAX_NUMBER = 10000000;

int value[MAX_NUMBER];
int number;
int n, m;
void dfs(long long cnt_number, int i, int j) {
    if (cnt_number > n) {
        return ;
    }
    if (cnt_number != 0) {
        value[number++] = cnt_number;
    }
    dfs(cnt_number * 10 + i, i, j);
    dfs(cnt_number * 10 + j, i, j);
}

void init() {
    m = 1;
    for (int i = 1; i < number; i++) {
        if (value[i] != value[i - 1]) {
            value[m] = value[i];
            m++;
        }
    }
}

int main() {

    number = 0;
    scanf("%d", &n);
    for (int i = 1; i <= 9; i++) {
        for (int j = i; j <= 9; j++) {
            dfs(0, i, j);
        }
    }
    for (int i = 1; i <= 9; i++) {
        dfs(i, 0, i);
    }
    sort(value, value + number);
    init();
    printf("%d\n", m);
    return 0;
}
