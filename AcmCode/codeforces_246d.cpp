#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
const int MAX_NUMBER = 100006;
struct Point {
    int number;
    int color;
};

struct Point point[MAX_NUMBER];
int value[MAX_NUMBER], vis[MAX_NUMBER];
vector<int> path[MAX_NUMBER];
set<int> color_number[MAX_NUMBER];
vector<int> all_color;
int point_number, edge_number;


bool cmp(struct Point a, struct Point b) {
    return a.color < b.color;
}


int main() {

    scanf("%d%d", &point_number, &edge_number);
    for (int i = 1; i <= point_number; i++) {
        scanf("%d", &point[i].color);
        value[i] = point[i].color;
        point[i].number = i;
    }
    sort(point + 1, point + 1 + point_number, cmp);
    for (int i = 1; i <= point_number; i++) {
        if (!vis[point[i].color]) {
            vis[point[i].color] = 1;
            all_color.push_back(point[i].color);
        }
    }
    for (int i = 1; i <= edge_number; i++) {
        int start, end;
        scanf("%d%d", &start, &end);
        path[start].push_back(end);
        path[end].push_back(start);
    }
    for (int i = 1; i <= point_number; i++) {
        int cnt_color = value[i];
        for (int j = 0; j < path[i].size(); j++) {
            int next_color = value[path[i][j]];
            if (next_color != cnt_color && !color_number[cnt_color].count(next_color)) {
                color_number[cnt_color].insert(next_color);
            }
        }
    }
    int max_number = - 1;
    int ans;
    for (int i = 0; i < all_color.size(); i++) {
        int cnt_color = all_color[i];
        if (max_number == -1 || max_number < color_number[cnt_color].size()) {
            max_number = color_number[cnt_color].size();
            ans = cnt_color;
        }
    }
    printf("%d\n", ans);
    return 0;
}
