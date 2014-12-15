#include <string.h>
#include <cstdio>
#include <algorithm>

#define MAX_NUMBER 50
#define MAX_LENGTH 12
#define max(a,b) ((a) > (b)) ? (a) : (b)

using namespace std;

struct Box {
    int dimension[MAX_LENGTH];
    int order;
};


struct Box box[MAX_NUMBER];
int maps[MAX_NUMBER][MAX_NUMBER];
int dimension_number, box_number, ans, final_point;
int dp[MAX_NUMBER], pre[MAX_NUMBER], out[MAX_NUMBER];

void buildGraph(int cnt_order) {
    for (int i = 1; i < cnt_order; i++) {
        int small = 0;
        int large = 0;
        for (int j = 0; j < dimension_number; j++) {
            if (box[cnt_order].dimension[j] <= box[i].dimension[j]) {
                small = 1;
                break;
            }
        }
        if (!small) {
            maps[i][cnt_order] = 1;
            out[i]++;
            continue;
        }
        for (int j = 0; j < dimension_number; j++) {
            if (box[cnt_order].dimension[j] >= box[i].dimension[j]) {
                large = 1;
                break;
            }
        }
        if (!large) {
            maps[cnt_order][i] = 1;
            out[cnt_order]++;
            continue;
        }
    }
}

int getLength(int cnt_order) {
    if (dp[cnt_order] != -1) {
        return dp[cnt_order];
    }
    else {
        for (int i = 1; i <= box_number; i++) {
            if (maps[cnt_order][i]) {
                getLength(i);
                if (dp[i] + 1 > dp[cnt_order]) {
                    dp[cnt_order] = dp[i] + 1;
                    pre[cnt_order] = i;
                }
                if (dp[cnt_order] > ans) {
                    ans = dp[cnt_order];
                }
            }
        }
    }
}

int main() {

    while (scanf("%d%d", &box_number, &dimension_number) != EOF) {
        memset(maps, 0, sizeof(maps));
        memset(out, 0, sizeof(out));
        memset(pre, -1, sizeof(pre));
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= box_number; i++) {
            for (int j = 0; j < dimension_number; j++) {
                scanf("%d", &box[i].dimension[j]);
            }
            sort(box[i].dimension, box[i].dimension + dimension_number);
            buildGraph(i);
        }
        for (int i = 1; i <= box_number; i++) {
            if (out[i] == 0) {
                pre[i] = -1;
                dp[i] = 1;
            }
        }
        for (int i = 1; i <= box_number; i++) {
            getLength(i);
        }
        ans = 0;
        for (int i = 1; i <= box_number; i++) {
            if (dp[i] > ans) {
                ans = dp[i];
                final_point = i;
            }
        }
        printf("%d\n", ans);
        int cnt_point = final_point;
        int flag = 0;
        while (cnt_point != -1) {
            if (!flag) {
                printf("%d", cnt_point);
                flag = 1;
            }
            else {
                printf(" %d", cnt_point);
            }
            cnt_point = pre[cnt_point];
        }
        printf("\n");
    }
    return 0;
}
