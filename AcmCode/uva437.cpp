#include <string.h>
#include <cstdio>
#include <vector>

#define MAX_NUMBER 200


using namespace std;

struct Block {
    int x;
    int y;
    int z;
};

vector<int> maps[MAX_NUMBER];
struct Block block[MAX_NUMBER];
int block_number, dp[MAX_NUMBER];

void buildMap() {
    for(int i = 0; i < block_number; i++) {
        for (int j = 0; j < block_number; j++) {
            if (block[i].x < block[j].x && block[i].y < block[j].y) {
                maps[i].push_back(j);
            }
        }
    }
}

void search(int cnt_point) {
    if (dp[cnt_point] != 0) {
        return ;
    }
    int ans = block[cnt_point].z;
    for (int i = 0; i < maps[cnt_point].size(); i++) {
        int next = maps[cnt_point][i];
        search(next);
        if (dp[next] + block[cnt_point].z > ans) {
            ans = dp[next] + block[cnt_point].z;
        }
    }
    dp[cnt_point] = ans;
}

int main() {

    int case_number = 1;
    while (scanf("%d", &block_number) != EOF) {
        if (!block_number) {
            break;
        }
        for (int i = 0; i < block_number; i++) {
            int cnt_x, cnt_y, cnt_z;
            scanf("%d%d%d", &cnt_x, &cnt_y, &cnt_z);
            block[i * 6 + 0].x = cnt_x, block[i * 6 + 0].y = cnt_y, block[i * 6 + 0].z = cnt_z;
            block[i * 6 + 1].x = cnt_y, block[i * 6 + 1].y = cnt_x, block[i * 6 + 1].z = cnt_z;
            block[i * 6 + 2].x = cnt_x, block[i * 6 + 2].y = cnt_z, block[i * 6 + 2].z = cnt_y;
            block[i * 6 + 3].x = cnt_z, block[i * 6 + 3].y = cnt_x, block[i * 6 + 3].z = cnt_y;
            block[i * 6 + 4].x = cnt_y, block[i * 6 + 4].y = cnt_z, block[i * 6 + 4].z = cnt_x;
            block[i * 6 + 5].x = cnt_z, block[i * 6 + 5].y = cnt_y, block[i * 6 + 5].z = cnt_x;   
        }
        block_number *= 6;
        for (int i = 0; i < block_number; i++) {
            maps[i].clear();
        }
        buildMap();
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        for (int i = 0; i < block_number; i++) {
            search(i);
            if (dp[i] > ans) {
                ans = dp[i];
            }
        }
        printf("Case %d: maximum height = %d\n", case_number, ans);
        case_number++;
    }
    return 0;
}
