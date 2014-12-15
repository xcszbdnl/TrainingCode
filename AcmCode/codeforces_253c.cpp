#include <cstdio>
#include <string.h>

const int MAX_NUMBER = 104;

int row;
int value[MAX_NUMBER];
int start_r, end_r, start_loc, end_loc;

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &row);
    for (int i = 1; i <= row; i++) {
        scanf("%d", &value[i]);
    }
    scanf("%d%d%d%d", &start_r, &end_r, &start_loc, &end_loc);
    
}
