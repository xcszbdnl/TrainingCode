#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_NUMBER 65537

struct Segment {
    int left;
    int right;
    int lazy;
    int cover;
};

struct Sets {
    int start;
    int end;
};


struct Segment segment[MAX_NUMBER * 4];
struct Sets sets[MAX_NUMBER];
int set_number;


void build(int order, int left, int right) {
    int mid = (left + right) / 2;
    segment[order].left = left;
    segment[order].right = right;
    segment[order].cover = 0;
    segment[order].lazy = 0;
    if (left == right) {
        return ;
    }
    build(order * 2, left, mid);
    build(order * 2 + 1, mid + 1, right);
}

void assignment(int order, int left, int right, int value) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left <= left && segment[order].right >= right) {
        segment[order].cover = value;
        segment[order].lazy = 0;
        return ;
    }
    if (segment[order].lazy) {
        segment[order * 2].cover = segment[order * 2 + 1].cover = segment[order].cover;
        segment[order].lazy = 0;
    }
    if (right <= mid) {
        assignment(order * 2, left, right);
    }
    else if (left > mid) {
        assignment(order * 2 + 1, left, right);
    }
    else {
        assignment(order * 2, left, mid);
        assignment(order * 2 + 1, mid + 1, right);
    }
}

void xorOperation(int order, int left, int right) {
    int mid = (segment[order].left + segment[order].right) / 2;
    if (segment[order].left <= left && segment[order].right >= right) {
        segment[order].cover = segment[order].cover ^ 1;
        segment[order].lazy = 1;
        return ;
    }
    if (segment[order].lazy) {
        segment[order * 2].cover = segment[order * 2 + 1].cover = segment[order].cover;
        segment[order].lazy = 0;
    }
    if (right <= mid) {
        xorOperation(order * 2 , left, right);
    }
    else if (left > mid){
        xorOperation(order * 2 + 1, left, right);
    }
    else {
        xorOperation(order * 2 , left, mid);
        xorOperation(order * 2 + 1, mid + 1, right);
    }
}

void search(int order) {
    if (segment[order].cover) {
        sets[set_number].start = segment[order].left;
        sets[set_number].end = segment[order].right;
        set_number++;
        return ;
    }
    search(order * 2);
    search(order * 2 + 1);
}

int main() {
    freopen("input.txt", "r", stdin);
    char operation, interval[10];
    int left, right, i;
    int cnt_number, next_number;
    build(1, 1, MAX_NUMBER);
    while (scanf("%c%s",operation, interval) != EOF) {
        getchar();
        left = 0;
        for (i = 1; interval[i] != ','; i++) {
            left = left * 10 + interval[i] - '0';
        }
        left++;
        if (interval[0] == '(') {
            left++;
        }
        right = 0;
        for (i++; interval[i] != ')' || interval[i] != ']'; i++) {
            right = right * 10 + interval[i] - '0';
        }
        if (interval[i] == ')') {
            right--;
        }
        switch(operation) {
        case 'U':
            assignment(1, left, right, 1);
            break;
        case 'I':
            if (left != 1) {
                assignment(1, 1, left - 1, 0);
            }
            if (right != MAX_NUMBER) {
                assignment(1, right + 1, MAX_NUMBER, 0);
            }
            break;
        case 'S':
            xorOperation(1, left, right);
            break;
        case 'D':
            assignment(1, left, right, 0);
            break;
        case 'C':
            if (left != 1) {
                assignment(1, 1, left - 1, 0);
            }
            if (right != MAX_NUMBER) {
                assignment(1, right + 1, MAX_NUMBER, 0);
            }
            xorOperation(1, left, right);
            break;
        }
    }
    search(1);
    sort(sets, sets + set_number, cmp);
    cnt_number = 0;
    if (set_number != 0) {
        for (i = 1; i < set_number; i++) {
            if (sets[cnt_number].end == sets[i].start + 1) {
                sets[cnt_number].end = sets[i].end;
            }
            else {
                cnt_number++;
                sets[cnt_number].start = sets[i].start;
                sets[cnt_number].end = sets[i].end;
            }
        }
        for (i = 0; i <= cnt_number; i++) {
            printf("(%d,%d)", sets[i].start - 2, sets[i].end + 2);
        }
    }
    else {
        printf("empty set\n");
    }
    return 0;
}

