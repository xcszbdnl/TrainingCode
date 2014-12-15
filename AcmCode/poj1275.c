#include <stdio.h>
#include <string.h>

#define MAX_POINT 50
#define DAYS_HOUR 24
#define MAX_EDGE 20000
#define MAX_PEOPLE 24000
#define INF 20000000


struct Edge {
    int start;
    int end;
    int value;
};

struct Edge edge[MAX_EDGE];
int needed_number[MAX_POINT], work_number[MAX_POINT];
int distance[MAX_POINT];
int edge_number;

void addEdge(int start, int end, int value) {
    edge[edge_number].start = start;
    edge[edge_number].end = end;
    edge[edge_number].value = value;
    edge_number++;
}

int bellmanFord() {
    int i, flag, k, cnt_start, cnt_end;
    for (i = 0; i <= DAYS_HOUR; i++) {
        distance[i] = -INF;
    }
    distance[0] = 0;
    for (i = 0; i < DAYS_HOUR; i++) {
        flag = 1;
        for (k = 0; k < edge_number; k++) {
            cnt_start = edge[k].start;
            cnt_end = edge[k].end;
            if (distance[cnt_start] != -INF && distance[cnt_end] < distance[cnt_start] + edge[k].value) {
                distance[cnt_end] = distance[cnt_start] + edge[k].value;
                flag = 0;
            }
        }
        if (flag) {
            break;
        }
    }
    for (k = 0; k < edge_number; k++) {
        cnt_start = edge[k].start;
        cnt_end = edge[k].end;
        if (distance[cnt_end] < distance[cnt_start] + edge[k].value) {
            return 0;
        }
    }
    return 1;
}

void build(int number) {
    int i, j;
    for (i = 1; i <= DAYS_HOUR; i++) {
        addEdge(i - 1, i, 0);
        addEdge(i , i - 1, -work_number[i]);
    }
    addEdge(0 , DAYS_HOUR, number);
    for (i = 1; i <= DAYS_HOUR; i++) {
        if (i >= 8) {
            addEdge(i - 8, i, needed_number[i]);
        }
        else {
            addEdge(16 + i, i, needed_number[i] - number);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int test_case, i, start_time, work_people, low, high, mid, flag, min_people, have_answer;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(map, 0, sizeof(map));
        memset(needed_number, 0, sizeof(needed_number));
        memset(work_number, 0, sizeof(work_number));
        flag = 0;
        for (i = 1; i <= DAYS_HOUR; i++) {
            scanf("%d", &needed_number[i]);
        }
        scanf("%d", &work_people);
        for (i = 0; i < work_people; i++) {
            scanf("%d", &start_time);
            work_number[start_time + 1]++;
        }
        low = 1, high = MAX_PEOPLE;
        have_answer = 0;
        while (low <= high) {
            edge_number = 0;
            mid = (low + high) / 2;
            build(mid);
            flag = bellmanFord();
            if (flag) {
                high = mid - 1;
                have_answer = 1;
            }
            else {
                low = mid + 1;
            }
        }
        if (!have_answer) {
            printf("No Solution\n");
        }
        else {
            printf("%d\n", low);
        }
    }
    return 0;
}
