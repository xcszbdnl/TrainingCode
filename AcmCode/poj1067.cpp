//                            _ooOoo_
//                           o8888888o
//                           88" . "88
//                           (| -_- |)
//                            O\ = /O
//                        ____/`---'\____
//                      .   ' \\| |// `.
//                       / \\||| : |||// \
//                     / _||||| -:- |||||- \
//                       | | \\\ - /// | |
//                     | \_| ''\---/'' | |
//                      \ .-\__ `-` ___/-. /
//                   ___`. .' /--.--\ `. . __
//                ."" '< `.___\_<|>_/___.' >'"".
//               | | : `- \`.;`\ _ /`;.`/ - ` : | |
//                 \ \ `-. \_ __\ /__ _/ .-` / /
//         ======`-.____`-.___\_____/___.-`____.-'======
//                            `=---='
//
//         .............................................
//                  ·ð×æ±£ÓÓ             ÓÀÎÞBUG

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>


const double e = ((1 + sqrt(5.0)) / 2);
using namespace std;

int main() {
//    freopen("in.txt", "r", stdin);
    int a, b;
    while (scanf("%d%d", &a, &b) != EOF) {
        if (a > b) {
            swap(a, b);
        }
        int j = a / e;
        int tmp;
        if (a == (int)(j * e)) {
            tmp = a + j;
        }
        else {
            j++;
            a = (int)(j * e);
            tmp = a + j;
        }
        if (tmp == b) {
            printf("0\n");
        }
        else {
            printf("1\n");
        }
    }
    return 0;
}
