#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;
const int MAX_NUMBER = 105;


int maps[MAX_NUMBER][MAX_NUMBER];
int point_number;
vector<int> ans[2];
vector<int> temp[2];

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &point_number) != EOF) {
        memset(maps, 0, sizeof(maps));
        for (int i = 1; i <= point_number; i++) {
            int know;
            while (1) {
                scanf("%d", &know);
                if (!know) {
                    break;
                }
                maps[i][know] = 1;
            }
        }
        int has_ans = 0;
        for (int i = 2; i <= point_number; i++) {
            int flag = 0;
            temp[1].clear();
            temp[2].clear();
            temp[1].push_back
        }
    }
    return 0;
}
