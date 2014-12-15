#include <cstdio>
#include <cstring>

const int MAX_NUMBER = 27;
const int MAX_NODE = 100007;

struct Trei {
    char child[27];
    int count;
    Trei() {
        memset(child, 0, sizeof(child));
        count = 0;
    }
};


struct Trei trei[MAX_NODE];


int main() {
}
