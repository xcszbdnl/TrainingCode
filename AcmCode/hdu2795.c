#include <stdio.h>

#define MAX_NUMBER 200005
#define max(a, b) ((a) > (b)) ? (a) : (b)


struct Segment {
    int left;
    int right;
    int max_number;
};

struct Segment segment[MAX_NUMBER * 4];

int width, height;
int point_number, announcement_width;

void build(int order, int left, int right) {
    int mid;
    segment[order].max_number = width;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        return ;
    }
    mid = (left + right) >> 1;
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

int query(int order, int query_width) {
    int mid, row;
    if (segment[order].left == segment[order].right) {
        segment[order].max_number -= query_width;
        return segment[order].left;
    }
    if (segment[order * 2].max_number < query_width ) {
        row = query(order * 2 + 1, query_width);
    }
    else {
        row = query(order * 2, query_width);
    }
    segment[order].max_number = max(segment[order * 2].max_number, segment[order * 2 + 1].max_number);
    return row;
    
}

int main() {

    int row;
    while (scanf("%d%d%d", &height, &width, &point_number) != EOF) {
        if (height > point_number) {
            height = point_number;
        }
        build(1, 1, height);
        while (point_number--) {
            scanf("%d", &announcement_width); 
            if (announcement_width > segment[1].max_number) {
                printf("-1\n");
                continue;
            }
            else {
                row = query(1, announcement_width);
                printf("%d\n", row);
            }
        }
    }
}
