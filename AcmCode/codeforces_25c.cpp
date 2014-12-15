#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
#define min(a,b) ((a) > (b)) ? (b) : (a)
const int MAX_NUMBER = 307;


int maps[MAX_NUMBER][MAX_NUMBER];


int main() {

    int point_number;
    scanf("%d", &point_number);
    for (int i = 1; i <= point_number; i++) {
        for (int j = 1; j <= point_number; j++) {
            scanf("%d", &maps[i][j]);
        }
    }
    int k;
    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        long long sums = 0;
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (c < maps[a][b]) {
            maps[a][b] = maps[b][a] = c;
        }
        for (int j = 1; j <= point_number; j++) {
            for (int k = 1; k <= point_number; k++) {
                maps[j][k] = min(min(maps[j][k], maps[j][a] + maps[a][b] + maps[b][k]), maps[j][b] + maps[b][a] + maps[a][k]);
                sums = sums + (long long)maps[j][k];
            }
        }
        cout << sums / 2 << " ";
    }
    printf("\n");
    return 0;
}
