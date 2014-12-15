#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;
const int maxn = 30000;
struct Block {
    int order;
    bool operator < (const Block &a) const {
        return order > a.order;
    }
};

struct Mem {
    int order, time;
    bool operator < (const Mem &a) const {
        return time > a.time;
    }
};
priority_queue<struct Block> que;
priority_queue<struct Mem> mem;
int time[maxn + 7], inque[maxn + 7];

int main() {
//    freopen("in.txt", "r", stdin);
    char c;
    int cnt_t;
    for (int i = 1; i <= maxn; i++) {
        inque[i] = 1;
        struct Block cnt;
        cnt.order = i;
        que.push(cnt);
    }
    while (scanf("%d %c", &cnt_t, &c) != EOF) {
        while (!mem.empty()) {
            struct Mem cnt_mem = mem.top();
            while (cnt_mem.time != time[cnt_mem.order]) {
                mem.pop();
                cnt_mem.time = time[cnt_mem.order];
                mem.push(cnt_mem);
                cnt_mem = mem.top();
            }
            if (cnt_mem.time <= cnt_t) {
                inque[cnt_mem.order] = 1;
                struct Block cnt_block;
                cnt_block.order = cnt_mem.order;
                que.push(cnt_block);
                mem.pop();
            }
            else {
                break;
            }
        }
        if (c == '+') {
            struct Block cnt_block = que.top();
            que.pop();
            time[cnt_block.order] = cnt_t + 600;
            inque[cnt_block.order] = 0;
            printf("%d\n", cnt_block.order);
            struct Mem cnt_mem;
            cnt_mem.order = cnt_block.order;
            cnt_mem.time = time[cnt_block.order];
            mem.push(cnt_mem);
        }
        else {
            int block_no;
            scanf("%d", &block_no);
            if (inque[block_no]) {
                printf("-\n");
            }
            else {
                printf("+\n");
                time[block_no] = cnt_t + 600;
            }
        }
    }
}

