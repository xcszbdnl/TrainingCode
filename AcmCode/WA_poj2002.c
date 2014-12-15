/**
 *FILENAME: poj2002.c
 *AUTHOR: XIANG CHANG SHENG
 *CREATE ON: 2013-2-3
 */

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_STARS 1005
#define PRIME 999983
#define MAX_MID 1000006
struct Coordinate {
    int x;
    int y;
};

struct MidStar {
    double mid_x;
    double mid_y;
    short coordinate_1;
    short coordinate_2;
};

int head[PRIME];
int next[MAX_MID];
struct Coordinate coor[MAX_STARS];
struct MidStar mid_star[MAX_MID];

int hashCode(int mid_star_number) {
    int hash_code = mid_star[mid_star_number].mid_x;
    hash_code *= 131;
    hash_code += mid_star[mid_star_number].mid_y;
    hash_code &= 0x7FFFFFFF;
    return hash_code % PRIME;
}

int main() {
    freopen("input.txt", "r", stdin);
    int stars_number, i, j, mid_star_number;
    int k, slope, previous_point;
    double x1_x2, x3_x2, y1_y2, y3_y2;
    int ans, distance_1, distance_2, hash_code;
    while (scanf("%d", &stars_number) != EOF) {
        if (!stars_number) {
            break;
        }
        ans = 0;
        memset(head, -1, sizeof(head));
        memset(next, -1, sizeof(next));
        for (i = 0; i < stars_number; i++) {
            scanf("%d%d", &coor[i].x, &coor[i].y);
        }
        for (i = 0; i < stars_number; i++) {
            for (j = 0; j < stars_number; j++) {
                if (i != j) {
                    mid_star[mid_star_number].mid_x = (coor[i].x + coor[j].x) / 2;
                    mid_star[mid_star_number].mid_y = (coor[i].y + coor[j].y) / 2;
                    mid_star[mid_star_number].coordinate_1 = i;
                    mid_star[mid_star_number].coordinate_2 = j;
                    hash_code = hashCode(mid_star_number);
                    for (k = head[hash_code]; k != -1; k = next[k]) {
                        previous_point = mid_star[k].coordinate_1;
                        x1_x2 = coor[i].x - mid_star[mid_star_number].mid_x;
                        x3_x2 = coor[previous_point].x - mid_star[mid_star_number].mid_x;
                        y1_y2 = coor[i].y - mid_star[mid_star_number].mid_y;
                        y3_y2 = coor[previous_point].y - mid_star[mid_star_number].mid_y;
                        slope = (y3_y2) * (y1_y2) + (x3_x2) * (x1_x2);
                        distance_1 = (y3_y2 * y3_y2 + x3_x2 * x3_x2);
                        distance_2 = (y1_y2 * y1_y2 + x1_x2 * x1_x2);
                        if (distance_1 - distance_2 <= 1e-6 && slope - 0 <= 1e-6) {
                            ans++;
                        }
                    }
                    next[mid_star_number] = head[hash_code];
                    head[hash_code] = mid_star_number;
                    mid_star_number++;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
