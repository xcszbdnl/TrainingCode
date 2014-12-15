#include <stdio.h>
#include <string.h>


#define MAX_NUMBER 250
#define SUPER_SOURCE 0
#define INF 1000000

int original_map[MAX_NUMBER][MAX_NUMBER];
int build_map[MAX_NUMBER][MAX_NUMBER];
int vis[MAX_NUMBER], father[MAX_NUMBER], queue[MAX_NUMBER];
int flow[MAX_NUMBER][MAX_NUMBER];
int machine_number, cows_number, process_number, super_source, super_destination, max_distance, min_distance;

void floyd() {
    int i, j, k;
    for (k = 1; k <= machine_number + cows_number; k++) {
        for (i = 1; i <= machine_number + cows_number; i++) {
            for (j = 1; j <= machine_number + cows_number; j++) {
                if (original_map[i][j] > original_map[i][k] + original_map[k][j]) {
                    original_map[i][j] = original_map[i][k] + original_map[k][j];
                    if (original_map[i][j] > max_distance) {
                        max_distance = original_map[i][j];
                    }
                }
            }
        }
    }
}

void buildGraph(int guess_distance) {
    int i, j;
    memset(build_map, 0, sizeof(build_map));
    for (i = machine_number + 1; i <= machine_number + cows_number; i++) {
        for (j = 1; j <= machine_number; j++) {
            if (original_map[i][j] <= guess_distance) {
                build_map[i][j] = 1;
            }
        }
    }
    for (i = machine_number + 1; i <= machine_number + cows_number; i++) {
        build_map[0][i] = 1;
    }
    for (i = 1; i <= machine_number; i++) {
        build_map[i][machine_number + cows_number + 1] = process_number;
    }
}

int edmondsKarp() {
    int value, i, front, rear, cnt_point, last_point;
    super_source = 0;
    super_destination = machine_number + cows_number + 1;
    value = 0;
    memset(flow, 0, sizeof(flow));
    while (1) {
        memset(vis, 0, sizeof(vis));
        front = 0;
        rear = 1;
        queue[front] = super_source;
        vis[super_source] = INF;
        while (front < rear) {
            cnt_point = queue[front];
            for (i = 0; i <= machine_number + cows_number + 1; i++) {
                if (!vis[i] && build_map[cnt_point][i] > flow[cnt_point][i]) {
                    father[i] = cnt_point;
                    queue[rear++] = i;
                    if (build_map[cnt_point][i] - flow[cnt_point][i] < vis[cnt_point]) {
                        vis[i] = build_map[cnt_point][i] - flow[cnt_point][i];
                    }
                    else {
                        vis[i] = vis[cnt_point];
                    }
                }
            }
            front++;
        }
        if (vis[super_destination] == 0) {
            break;
        }
        for (last_point = super_destination; last_point != super_source; last_point = father[last_point]) {
            flow[father[last_point]][last_point] += vis[super_destination];
            flow[last_point][father[last_point]] -= vis[super_destination];
        }
        value += vis[super_destination];
    }
    return value;
}

int main() {

    int i, j, low, high, mid, value;
    scanf("%d%d%d", &machine_number, &cows_number, &process_number);
    for (i = 1; i <= machine_number + cows_number; i++) {
        for (j = 1; j <= machine_number + cows_number; j++) {
            scanf("%d", &original_map[i][j]);
            if (original_map[i][j] == 0) {
                original_map[i][j] = INF;
            }
        }
    }
    max_distance = min_distance = 0;
    floyd();
    low = min_distance;
    high = max_distance;
    while (low <= high) {
        mid = (low + high) / 2;
        buildGraph(mid);
        value = edmondsKarp();
        if (value == cows_number) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    printf("%d\n", low);
    return 0;
}
