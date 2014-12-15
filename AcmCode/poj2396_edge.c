#include <stdio.h>
#include <string.h>


#define MAX_POINT 250
#define MAX_EDGE 20000
#define INF 1000000
#define max(a,b) ((a) > (b)) ? (a) : (b)
#define min(a,b) ((a) > (b)) ? (b) : (a)

struct Edge {
    int start;
    int end;
    int cap;
    int next;
};

struct Edge edge[MAX_EDGE];
int high[MAX_POINT][MAX_POINT], low[MAX_POINT][MAX_POINT], stack[MAX_POINT], queue[MAX_POINT], distance[MAX_POINT], number[MAX_POINT][MAX_POINT], head[MAX_POINT];
int in[MAX_POINT], out[MAX_POINT], cur[MAX_POINT], source, destination, super_source, super_destination, edge_number, row, column;

void addEdge(int start, int end, int value_1, int value_2) {
    edge[++edge_number].start = start;
    edge[edge_number].end = end;
    edge[edge_number].cap = value_1;
    edge[edge_number].next = head[start];
    head[start] = edge_number;

    edge[++edge_number].start = end;
    edge[edge_number].end = start;
    edge[edge_number].cap = value_2;
    edge[edge_number].next = head[end];
    head[end] = edge_number;
}

void init() {
    edge_number = 1;
    memset(high, 0, sizeof(high));
    memset(low, 0, sizeof(low));
    memset(number, 0, sizeof(number));
    memset(head, -1, sizeof(head));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
}

void build(int row_1, int column_1, int lower, int upper) {
    int i, j;
    if (row_1 && column_1) {
        high[row_1][column_1] = min(high[row_1][column_1], upper);
        low[row_1][column_1] = max(low[row_1][column_1], lower);
    }
    else if (!row_1 && column_1) {
        for (i = 1; i <= row; i++) {
            high[i][column_1] = min(high[i][column_1], upper);
            low[i][column_1] = max(low[i][column_1], lower);
        }
    }
    else if (row_1 && !column_1) {
        for (i = 1; i <= column; i++) {
            high[row_1][i] = min(high[row_1][i], upper);
            low[row_1][i] = max(low[row_1][i], lower);
        }
    }
    else if (!row_1 && !column_1) {
        for (i = 1; i <= row; i++) {
            for (j = 1; j <= column; j++) {
                high[i][j] = min(high[i][j], upper);
                low[i][j] = max(low[i][j], lower);
            }
        }
    }
}

int bfs() {
    int i, front, rear, cnt_point, next_point;
    memset(distance, -1, sizeof(distance));
    front = 0;
    rear = 1;
    queue[front] = super_source;
    distance[super_source] = 0;
    while (front < rear) {
        cnt_point = queue[front];
        for (i = head[cnt_point]; i != -1; i = edge[i].next) {
            next_point = edge[i].end;
            if (edge[i].cap > 0 && distance[next_point] == -1) {
                distance[next_point] = distance[cnt_point] + 1;
                queue[rear] = next_point;
                rear++;
                if (next_point == super_destination) {
                    return 1;
                }
            }
        }
        front++;
    }
    return 0;
}

int dinic() {
    int stack[MAX_POINT], top, cnt_point, min_flow, pre_top, max_flow, end, i;
    max_flow = 0;
    while (bfs()) {
        memcpy(cur, head, sizeof(head));
        top = 0;
        cnt_point = super_source;
        while (1) {
            if (cnt_point == super_destination) {
                min_flow = INF;
                for (i = 0; i < top; i++) {
                    if (min_flow > edge[stack[i]].cap) {
                        min_flow = edge[stack[i]].cap;
                        pre_top = i;
                    }
                }
                max_flow += min_flow;
                for (i = 0; i < top; i++) {
                    edge[stack[i]].cap -= min_flow;
                    edge[stack[i] ^ 1].cap += min_flow;
                }
                top = pre_top;
                cnt_point = edge[stack[top]].start;
            }
            for (i = cur[cnt_point]; i != -1; cur[cnt_point] = i = edge[i].next) {
                end = edge[i].end;
                if (edge[i].cap > 0 && distance[end] == distance[cnt_point] + 1) {
                    break;
                }
            }
            if (cur[cnt_point] != -1) {
                stack[top++] = cur[cnt_point];
                cnt_point = edge[cur[cnt_point]].end;
            }
            else {
                if (top == 0) {
                    break;
                }
                else {
                    distance[cnt_point] = -1;
                    top--;
                    cnt_point = edge[stack[top]].start;
                }
            }
        }
    }
    return max_flow;
}

int main() {
    freopen("input.txt", "r", stdin);
    int i, j, row_1, column_1, test_case, con_number, con, plus;
    int row_sum, column_sum, max_flow, sums, flag;
    char symbol;
    scanf("%d", &test_case);
    while (test_case--) {
        init();
        flag = 1;
        scanf("%d%d", &row, &column);
        source = 0;
        destination = row + column + 1;
        super_source = row + column + 2;
        super_destination = row + column + 3;
        for (i = 1; i <= row; i++) {
            for (j = 1; j <= column; j++) {
                high[i][j] = INF;
            }
        }
        for (i = 1; i<= row; i++) {
            scanf("%d", &row_sum);
            in[i] += row_sum;
            out[source] += row_sum;
        }
        for (i = 1; i <= column; i++) {
            scanf("%d", &column_sum);
            out[i + row] += column_sum;
            in[destination] += column_sum;
        }
        scanf("%d", &con_number);
        for (i = 1; i <= con_number; i++) {
            scanf("%d %d %c %d", &row_1, &column_1, &symbol, &con);
            if (symbol == '=') {
                build(row_1, column_1, con, con);
            }
            else if (symbol == '>') {
                build(row_1, column_1, con + 1, INF);
            }
            else {
                build(row_1, column_1, 0, con - 1);
            }
        }
        for (i = 1; i <= row; i++) {
            for (j = 1; j <= column ; j++) {
                out[i] += low[i][j];
                in[j + row] += low[i][j];
                if (high[i][j] - low[i][j] < 0) {
                    flag = 0;
                }
                addEdge(i, j + row, high[i][j] - low[i][j], 0);
                number[i][j] = edge_number;
            }
        }
        sums = 0;
        for (i = 0; i <= destination; i++) {
            plus = in[i] - out[i];
            if (plus > 0) {
                sums += plus;
                addEdge(super_source, i, plus, 0);
            }
            else {
                addEdge(i, super_destination, -plus, 0);
            }
        }
        addEdge(destination, source, INF, 0);
        max_flow = dinic();
        if (max_flow != sums) {
            flag = 0;
        }
        if (flag) {
            for (i = 1; i <= row; i++) {
                printf("%d", low[i][1] + edge[number[i][1]].cap);
                for (j = 2; j <= column; j++) {
                    printf(" %d", low[i][j] + edge[number[i][j]].cap);
                }
                printf("\n");
            }
        }
        else {
            printf("IMPOSSIBLE\n");
        }
        printf("\n");
    }
    return 0;
}
