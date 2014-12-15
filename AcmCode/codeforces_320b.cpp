#include <cstdio>
#include <string.h>
#include <vector>

using namespace std;

const int MAX_NUMBER = 105;

int maps[MAX_NUMBER][MAX_NUMBER];


struct Segment {
    int left;
    int right;
};

struct Segment segment[MAX_NUMBER];
int vis[MAX_NUMBER];
vector<int> path[MAX_NUMBER];
int query_number, segment_number, start, end, flag;

void add() {
    for (int i = 1; i < segment_number; i++) {
        if (segment[i].left > segment[segment_number].left && segment[i].left < segment[segment_number].right) {
            path[i].push_back(segment_number);
        }
        if (segment[i].right > segment[segment_number].left && segment[i].right < segment[segment_number].right) {
            path[i].push_back(segment_number);
        }
        if (segment[segment_number].left > segment[i].left && segment[segment_number].left < segment[i].right) {
            path[segment_number].push_back(i);
        }
        if (segment[segment_number].right > segment[i].left && segment[segment_number].right < segment[i].right) {
            path[segment_number].push_back(i);
        }
    }
}

void dfs(int cnt_seg) {
    if (cnt_seg == end) {
        maps[start][end] = 1;
        flag = 1;
        return ;
    }
    for (int i = 0; i < path[cnt_seg].size() && !flag; i++) {
        int next_seg = path[cnt_seg][i];
        if (!vis[next_seg]) {
            vis[next_seg] = 1;
            dfs(next_seg);
        }
    }
}


int main() {

    scanf("%d", &query_number);
    memset(maps, 0, sizeof(maps));
    segment_number = 0;
    for (int i = 1; i <= query_number; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            segment_number++;
            scanf("%d%d", &segment[segment_number].left, &segment[segment_number].right);
            add();
        }
        else {
            int seg_1, seg_2;
            scanf("%d%d", &start, &end);
            if (maps[start][end]) {
                printf("YES\n");
            }
            else {
                memset(vis, 0, sizeof(vis));
                flag = 0;
                dfs(start);
                if (maps[start][end]) {
                    printf("YES\n");
                }
                else {
                    printf("NO\n");
                }
            }
        }
    }
    return 0;
}
