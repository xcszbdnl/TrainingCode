#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 100020
#define max(a,b) ((a) > (b)) ? (a) : (b)


struct Segment {
    int left;
    int right;
    int black_length, left_black, right_black;
    int white_length, left_white, right_white;
    int lazy;
};


struct Segment segment[MAX_NUMBER * 5];
int stones[MAX_NUMBER];

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void pushUp(int order) {
    int mid_length;
    int left_length = segment[order * 2].right - segment[order * 2].left + 1;
    int right_length = segment[order * 2 + 1].right - segment[order * 2 + 1].left + 1;
    
    segment[order].black_length = max(segment[order * 2].black_length, segment[order * 2 + 1].black_length);
    mid_length = segment[order * 2].right_black + segment[order * 2 + 1].left_black;
    segment[order].black_length = max(mid_length, segment[order].black_length);
    
    segment[order].white_length = max(segment[order * 2].white_length, segment[order * 2 + 1].white_length);
    mid_length = segment[order * 2].right_white + segment[order * 2 + 1].left_white;
    segment[order].white_length = max(mid_length, segment[order].white_length);
    
    segment[order].left_black = segment[order * 2].left_black;
    if (segment[order * 2].left_black == left_length) {
        segment[order].left_black = segment[order * 2].left_black + segment[order * 2 + 1].left_black;
    }
    
    segment[order].right_black = segment[order * 2 + 1].right_black;
    if (segment[order * 2 + 1].right_black == right_length) {
        segment[order].right_black = segment[order * 2 + 1].right_black + segment[order * 2].right_black;
    }
    
    segment[order].left_white = segment[order * 2].left_white;    
    if (segment[order * 2].left_white == left_length) {
        segment[order].left_white = segment[order * 2].left_white + segment[order * 2 + 1].left_white;
    }
    
    segment[order].right_white = segment[order * 2 + 1].right_white;
    if (segment[order * 2 + 1].right_white == right_length) {
        segment[order].right_white = segment[order * 2 + 1].right_white + segment[order * 2].right_white;
    }
}

void swapBlackWhite(int order) {
    swap(&segment[order].white_length, &segment[order].black_length);
    swap(&segment[order].right_black, &segment[order].right_white);
    swap(&segment[order].left_black, &segment[order].left_white);
}

void pushDown(int order) {
    if (segment[order].lazy) {
        swapBlackWhite(order * 2);
        segment[order * 2].lazy ^= 1;
        swapBlackWhite(order * 2 + 1);
        segment[order * 2 + 1].lazy ^= 1;
        segment[order].lazy ^= 1;
    }
}

void build(int order, int left, int right) {
    int mid = (left + right) >> 1;
    segment[order].left = left;
    segment[order].right = right;
    if (left == right) {
        if (stones[left]) {
            segment[order].black_length = segment[order].left_black = segment[order].right_black = 1;
            segment[order].white_length = segment[order].left_white = segment[order].right_white = 0;
        }
        else {
            segment[order].black_length = segment[order].left_black = segment[order].right_black = 0;
            segment[order].white_length = segment[order].left_white = segment[order].right_white = 1;            
        }
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
    pushUp(order);
}

void update(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    if (segment[order].left >= left && segment[order].right <= right) {
        swapBlackWhite(order);
        segment[order].lazy ^= 1;
        return ;
    }
    pushDown(order);
    if (right <= mid) {
        update(order * 2, left, right);
    }
    else if (left > mid) {
        update(order * 2 + 1, left, right);
    }
    else {
        update(order * 2, left, mid);
        update(order * 2 + 1, mid + 1, right);
    }
    pushUp(order);
}

int query(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) >> 1;
    int left_answer, right_answer, mid_answer, final_answer;
    if (segment[order].left >= left && segment[order].right <= right) {
        return segment[order].black_length;
    }
    pushDown(order);
    if (right <= mid) {
        return query(order * 2, left, right);
    }
    else if (left > mid) {
        return query(order * 2 + 1, left, right);
    }
    else {
        left_answer = query(order * 2, left, mid);
        right_answer = query(order * 2 + 1, mid + 1, right);
        mid_answer = segment[order * 2].right_black + segment[order * 2 + 1].left_black;
        final_answer = max(left_answer, right_answer);
        final_answer = max(final_answer, mid_answer);
        return final_answer;
    }
}

int main() {

    int stone_number, left, right, operation, operation_number, i, ans;
    while (scanf("%d", &stone_number) != EOF) {
        for (i = 1; i <= stone_number; i++) {
            scanf("%d", &stones[i]);
        }
        build(1, 1, stone_number);
        scanf("%d", &operation_number);
        for (i = 0; i < operation_number; i++) {
            scanf("%d%d%d", &operation, &left, &right);
            if (operation) {
                update(1, left, right);
            }
            else {
                ans = query(1, left, right);
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
