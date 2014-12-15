#include <stdio.h>


#define MAX_NUMBER 200005


struct Segment {
    int left;
    int right;
    int unseated;
};


struct Segment segment[MAX_NUMBER * 4];
int position[MAX_NUMBER], value[MAX_NUMBER], ans[MAX_NUMBER];

int build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    segment[order].unseated = (right - left) + 1;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

int query(int order, int pos) {
    int index;
    segment[order].unseated--;
    if (segment[order].left == segment[order].right) {
        return segment[order].left;
    }
    if (segment[order * 2].unseated >= pos) {
        index = query(order * 2, pos);
    }
    else {
        pos = pos - segment[order * 2].unseated;
        index = query(order * 2 + 1, pos);
    }
    return index;
}


int main() {

    int people_number;
    int i, location; 
    while (scanf("%d", &people_number) != EOF) {
        for (i = 0; i < people_number; i++) {
            scanf("%d%d", &position[i], &value[i]);
        }
        build(1, 1, people_number);
        for (i = people_number - 1; i >= 0; i--) {
            location = query(1, position[i] + 1);
            ans[location] = value[i];
        }
        for (i = 1; i <= people_number; i++) {
            if (i == 1) {
                printf("%d", ans[i]);
            }
            else {
                printf(" %d", ans[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
