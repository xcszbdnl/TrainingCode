#include <cstdio>
#include <cstring>


const int MAX_NUMBER = 1007;
struct Road {
    int start, end;
};
int father[MAX_NUMBER];
int point_number;
struct Road build[MAX_NUMBER];
struct Road close[MAX_NUMBER];
int find(int x) {
    if (x == father[x]) {
        return x;
    }
    father[x] = find(father[x]);
    return father[x];
}

int main() {

    scanf("%d", &point_number);
    for (int i = 1; i <= point_number; i++) {
        father[i] = i;
    }
    int close_number = 0;
    int build_number = 0;
    for (int i = 1; i < point_number; i++) {
        int start, end;
        scanf("%d%d", &start, &end);
        int x = find(start);
        int y = find(end);
        if (x != y) {
            father[y] = x;
        }
        else {
            close[++close_number].start = start;
            close[close_number].end = end;
        }
    }
    for (int i = 1; i <= point_number; i++) {
        for (int j = i + 1; j <= point_number; j++) {
            int x = find(i);
            int y = find(j);
            if (x != y) {
                build[++build_number].start = i;
                build[build_number].end = j;
                father[y] = x;
            }
        }
    }
    printf("%d\n", close_number);
    for (int i = 1; i <= close_number; i++) {
        printf("%d %d %d %d\n", close[i].start, close[i].end, build[i].start, build[i].end);
    }
    return 0;
}
