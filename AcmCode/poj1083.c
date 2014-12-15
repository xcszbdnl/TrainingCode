#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 105
#define MAX_CORRIDOR 300

struct Point {
    int start;
    int end;
};
struct Point point[MAX_NUMBER];
int vis[MAX_CORRIDOR];

int main() {

    int test_case, table_number, region_number, temp;
    int i, j;
    scanf("%d", &test_case);
    while (test_case--) {
        scanf("%d", &table_number);
        memset(vis, 0, sizeof(vis));
        region_number = 0;
        for (i = 1; i <= table_number; i++) {
            scanf("%d%d", &point[i].start, &point[i].end);
            if (point[i].start > point[i].end) {
                temp = point[i].start;
                point[i].start = point[i].end;
                point[i].end = temp;
            }
            point[i].start = (point[i].start + 1) / 2;
            point[i].end = (point[i].end + 1) / 2;
            for (j = point[i].start; j <= point[i].end; j++) {
                vis[j]++;
            }
        }
        for (j = 0; j <= MAX_CORRIDOR; j++) {
            if(vis[j] > region_number) {
                region_number = vis[j];
            }
        }
        printf("%d\n", region_number * 10);
    }
    return 0;
}
