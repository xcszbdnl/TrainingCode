#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 30

int map[MAX_NUMBER][MAX_NUMBER];
int in_degree[MAX_NUMBER];
int original_degree[MAX_NUMBER];
int n, m;
char ans[MAX_NUMBER];

int topSort() {
    int i, j;
    int zero_point, flag = 1;
    memset(ans, 0, sizeof(ans));
    memcpy(in_degree, original_degree, sizeof(original_degree));
    for (i = 0; i < n; i++) {
        zero_point = -1;
        for (j = 0; j < n; j++) {
            if (in_degree[j] == 0) {
                if (zero_point == -1) {
                    zero_point = j;
                }
                else {
                    flag = 0;
                }
            }
        }
        if (zero_point == -1) {
            return 2;
        }
        in_degree[zero_point] = -1;
        ans[i] = zero_point + 'A';
        for (j = 0; j < n; j++) {
            if (map[zero_point][j]) {
                in_degree[j]--;
            }
        }
    }
    if (flag) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {

    int i, flag;
    char relation[MAX_NUMBER];
    while (scanf("%d%d", &n, &m) != EOF) {
        if (!n && !m) {
            break;
        }
        flag = 0;
        memset(map, 0, sizeof(map));
        memset(original_degree, 0, sizeof(original_degree));
        for (i = 1; i <= m; i++) {
            scanf("%s", relation);
            map[relation[0] - 'A'][relation[2] - 'A'] = 1;
            original_degree[relation[2] - 'A']++;
            if (flag == 1 || flag == 2) {
                continue;
            }
            
            flag = topSort();
            if (flag == 1) {
                printf("Sorted sequence determined after %d relations: %s.\n", i, ans);
            }
            else if (flag == 2) {
                printf("Inconsistency found after %d relations.\n", i);
            }
        }
        if (!flag) {
            printf("Sorted sequence cannot be determined.\n");
        }
    }
    return 0;
}
