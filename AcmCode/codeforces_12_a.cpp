#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>


using namespace std;

char s[10][10];
int maps[3][3][2] =
{2,2,2,1,2,0,1,2,1,1,1,0,0,2,0,1,0,0};
int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%s%s%s", s[0], s[1], s[2]);
    int flag = 0;
    for (int i = 0; i < 3 && !flag; i++) {
        for (int j = 0; j < 3; j++) {
            if (s[i][j] == 'X') {
                int x = maps[i][j][0];
                int y = maps[i][j][1];
                if (s[x][y] != 'X') {
//                    printf("%d %d\n", i, j);
                    flag = 1;
                    break;
                }
            }
        }
    }
    if (!flag) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
    return 0;
}
