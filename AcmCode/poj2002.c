/**
 *FILENAME: poj2002.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2013-2-4
 */
#include <stdio.h>
#include <string.h>


/**
 *DESCRIPTION:
 Hash to sovle the problem
 */

#define MAX_NUMBER 1005
#define PRIME 1999
struct Star {
    int x;
    int y;
};

int head[PRIME];
int next[MAX_NUMBER];
struct Star star[MAX_NUMBER];

int hashCode(int order) {
    int hash_code = 0;
    hash_code = star[order].x * star[order].x + star[order].y * star[order].y;
    return hash_code % PRIME;
}

int find(struct Star point) {
    int hash_code = point.x * point.x + point.y * point.y;
    int j;
    hash_code = hash_code % PRIME;
    for (j = head[hash_code]; j != -1; j = next[j]) {
        if (point.x == star[j].x && point.y == star[j].y) {
            return 1;
        }
    }
    return 0;
}
int main() {
    freopen("input.txt", "r", stdin);
    int star_number, i, j, ans, hash_code;
    struct Star next_point_1, next_point_2;
    while (scanf("%d", &star_number) != EOF) {
        if (!star_number) {
            break;
        }
        memset(head, -1, sizeof(head));
        memset(next, -1, sizeof(next));
        ans = 0;
        for (i = 0; i < star_number; i++) {
            scanf("%d%d", &star[i].x, &star[i].y);
            hash_code = hashCode(i);
            next[i] = head[hash_code];
            head[hash_code] = i;
        }

        for (i = 0; i < star_number; i++) {
            for (j = i + 1; j < star_number; j++) {
                next_point_1.x = star[i].x + (star[i].y - star[j].y);
                next_point_1.y = star[i].y - (star[i].x - star[j].x);
                next_point_2.x = star[j].x + (star[i].y - star[j].y);
                next_point_2.y = star[j].y - (star[i].x - star[j].x);
                if (find(next_point_1) && find(next_point_2)) {
                    ans++;
                }
                next_point_1.x = star[i].x - (star[i].y - star[j].y);
                next_point_1.y = star[i].y + (star[i].x - star[j].x);
                next_point_2.x = star[j].x - (star[i].y - star[j].y);
                next_point_2.y = star[j].y + (star[i].x - star[j].x);
                if (find(next_point_1) && find(next_point_2)) {
                    ans++;
                }
            }
        }
        printf("%d\n", ans / 4);
    }
}
