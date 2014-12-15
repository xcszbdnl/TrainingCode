#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
const int MAX_NUMBER = 100007;
struct Edge {
    int start;
    int end;
    long long dist;
    int next;
};
vector<int> path[MAX_NUMBER];
long long dp[MAX_NUMBER], sums[MAX_NUMBER], dist[MAX_NUMBER], value[MAX_NUMBER];
int head[MAX_NUMBER], vis[MAX_NUMBER], father[MAX_NUMBER];
struct Edge edge[MAX_NUMBER * 2];
int point_number, edge_number;

void dfs(int cnt_point) {
    for (int next_edge = head[cnt_point]; next_edge != -1; next_edge = edge[next_edge].next) {
        int end = edge[next_edge].end;
        if (!vis[end]) {
            father[end] = cnt_point;
            value[end] = edge[next_edge].dist;
            vis[end] = 1;
            dfs(end);
            sums[cnt_point] += sums[end] + edge[next_edge].dist;
        }
    }
    if (path[cnt_point].size() == 1 && cnt_point != 1) {
        dp[cnt_point] = 0;
        return ;
    }
    else {
        long long total_dist = 2 * sums[cnt_point];
        for (int next_edge = head[cnt_point]; next_edge != -1; next_edge = edge[next_edge].next) {
            int end = edge[next_edge].end;
            if (end != father[cnt_point]) {
                long long temp_min = total_dist - 2 * sums[end] - value[end] + dp[end];
                if (dp[cnt_point] == 0 || dp[cnt_point] > temp_min) {
                    dp[cnt_point] = temp_min;
                }
            }
        }
    }
}

void addEdge(int start, int end, long long dist) {
    edge[edge_number].start = start;
    edge[edge_number].end = end;
    edge[edge_number].dist = dist;
    edge[edge_number].next = head[start];
    head[start] = edge_number;
    edge_number++;

    edge[edge_number].start = end;
    edge[edge_number].end = start;
    edge[edge_number].dist = dist;
    edge[edge_number].next = head[end];
    head[end] = edge_number;
    edge_number++;
}
int main() {

    memset(head, -1, sizeof(head));
    memset(dist, 0, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    memset(dp, 0, sizeof(dp));
    edge_number = 0;
    scanf("%d", &point_number);
    for (int i = 1; i < point_number; i++) {
        int start, end;
        long long dist;
        cin >> start >> end >> dist;
        path[start].push_back(end);
        path[end].push_back(start);
        addEdge(start, end, dist);
    }
    father[1] = -1;
    vis[1] = 1;
    dfs(1);
    cout << dp[1] << endl;
    return 0;
}
