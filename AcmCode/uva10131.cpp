#include <string.h>
#include <cstdio>
#include <vector>


#define MAX_NUMBER 1100

using namespace std;

struct Elephant {
    int weight;
    int iq;
    int order;
};

struct Elephant elephant[MAX_NUMBER];
vector<int> path[MAX_NUMBER];
int out[MAX_NUMBER], pre[MAX_NUMBER], result[MAX_NUMBER];
int dp[MAX_NUMBER];
int elephant_number = 1;


void buildGraph() {
    for (int i = 1; i < elephant_number; i++) {
        if (elephant[i].weight > elephant[elephant_number].weight && elephant[i].iq < elephant[elephant_number].iq) {
            path[i].push_back(elephant_number);
            out[i]++;
        }
        else if (elephant[i].weight < elephant[elephant_number].weight && elephant[i].iq > elephant[elephant_number].iq) {
            path[elephant_number].push_back(i);
            out[elephant_number]++;
        }
    }
}

void search(int cnt_point) {
    if (dp[cnt_point] != -1) {
        return ;
    }
    int ans = 0;
    for (int i = 0; i < path[cnt_point].size(); i++) {
        int next_point = path[cnt_point][i];
        search(next_point);
        if (dp[next_point] + 1 > dp[cnt_point]) {
            dp[cnt_point] = dp[next_point] + 1;
            pre[cnt_point] = next_point;
        }
    }
}

int main() {

    elephant_number = 1;
    while (scanf("%d%d", &elephant[elephant_number].weight, &elephant[elephant_number].iq) != EOF) {
        buildGraph();
        elephant_number++;
    }
    memset(dp, -1, sizeof(dp));
    memset(pre, -1, sizeof(pre));
    for (int i = 1; i <= elephant_number; i++) {
        if (out[i] == 0) {
            dp[i] = 1;
        }
    }
    for (int i = 1; i <= elephant_number; i++) {
        search(i);
    }
    int ans = 0;
    int final_point;
    for (int i = 1; i <= elephant_number; i++) {
        if (dp[i] > ans) {
            ans = dp[i];
            final_point = i;
        }
    }
    printf("%d\n", ans);
    int ans_number = 0;
    while (final_point != -1) {
        result[++ans_number] = final_point;
        final_point = pre[final_point];
    }
    for (int i = ans_number; i >= 1; i--) {
        printf("%d\n", result[i]);
    }
    return 0;
}
