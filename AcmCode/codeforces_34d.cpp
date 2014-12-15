#include <cstring>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_NUMBER = 50006;

vector<int> path[MAX_NUMBER];
int father[MAX_NUMBER], vis[MAX_NUMBER];
int point_number, pre_center, final_center;

void dfs(int cnt_point) {
    vis[cnt_point] = 1;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!vis[next_point]) {
            father[next_point] = cnt_point;
            dfs(next_point);
        }
    }
}

int main() {

    scanf("%d%d%d", &point_number, &pre_center, &final_center);
    for (int i = 1; i <= point_number; i++) {
        if (i != pre_center) {
            int temp;
            scanf("%d", &temp);
            path[temp].push_back(i);
            path[i].push_back(temp);
        }
    }
    memset(vis, 0, sizeof(vis));
    dfs(final_center);
    int first = 1;
    for (int i = 1; i <= point_number; i++) {
        if (i != final_center) {
            if (first) {
                printf("%d", father[i]);
                first = 0;
            }
            else {
                printf(" %d", father[i]);
            }
        }
    }
    printf("\n");
    return 0;
}

