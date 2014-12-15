#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 20006;
vector<int> path[MAX_NUMBER];
int vis[MAX_NUMBER];
int number[MAX_NUMBER];
int ans_number, ans_node;
int point_number;

void dfs(int cnt_point) {
    number[cnt_point] = 1;
    int temp_max = 0;
    int temp_point = point_number - 1;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        if (!vis[next_point]) {
            vis[next_point] = 1;
            dfs(next_point);
            number[cnt_point] += number[next_point];
            temp_point -= number[next_point];
            if (temp_max < number[next_point]) {
                temp_max = number[next_point];
            }
        }
    }
    if (temp_point > temp_max) {
        temp_max = temp_point;
    }
    if (temp_max < ans_number) {
        ans_number = temp_max;
        ans_node = cnt_point;
    }
}

int main() {

    int test_case;
    scanf("%d", &test_case);
    while (test_case--) {
        memset(vis, 0, sizeof(vis));
        memset(number, 0, sizeof(number));
        ans_number = MAX_NUMBER;
        scanf("%d", &point_number);
        for (int i = 1; i <= point_number; i++) {
            path[i].clear();
        }
        for (int i = 1; i < point_number; i++) {
            int start, end;
            scanf("%d%d", &start, &end);
            path[start].push_back(end);
            path[end].push_back(start);
        }
        dfs(1);
        printf("%d %d\n", ans_node, ans_number);
    }
    return 0;
}
