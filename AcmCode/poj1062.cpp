#include <cstdio>
#include <string.h>


#define MAX_NUMBER 110

struct Edge {
    int end;
    int value;
    int next;
};

struct Object {
    int value;
    int level;
    int rely_number;
    int rely[MAX_NUMBER];
};

struct Object object[MAX_NUMBER];
struct Edge edge[MAX_NUMBER * MAX_NUMBER];
int original_maps[MAX_NUMBER][MAX_NUMBER];
int level[MAX_NUMBER], head[MAX_NUMBER];
int level_plus, object_number;

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &level_plus, &object_number);
    for (int i = 1; i <= object_number; i++) {
        scanf("%d%d%d", &object[i].value, &object[i].level, &object[i].rely_number);
        for (int j = 1; j <= object[i].rely_number; j++) {
            int value, order;
            scanf("%d%d", &order, &value);
            maps[i][order] = value;
            
        }
    }
}
