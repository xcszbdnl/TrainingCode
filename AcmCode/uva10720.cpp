#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
using namespace std;
const int MAX_NUMBER = 100010;
int degrees[MAX_NUMBER];
int n_vertice;
int has_found;
bool cmp(int a,int b) {
    if(a > b)
        return true;
    else
        return false;
}
bool solve() {
    for(int i = 0; i < n_vertice; i++) {
        sort(degrees + i,degrees + n_vertice,cmp);
        int first_degree = degrees[i];
        if(first_degree > n_vertice)
            return false;
        if(!first_degree)
            return true;
        for(int j = i + 1; j <= i + first_degree; j++) {
            degrees[j]--;
            if(degrees[j] < 0) {
                return false;
            }
        }
    }
    return true;
        
}
        
int main() {
    freopen("input.txt","r",stdin);
    while(1) {
        cin >> n_vertice;
        if(!n_vertice) {
            break;
        }
        memset(degrees,0,sizeof(degrees));
        has_found = 0;
        for(int i = 0; i < n_vertice; i++) {
            cin >> degrees[i];
        }
        if(!solve()) {
            cout << "Not possible" << endl;
        }
        else {
            cout << "Possible" << endl;
        }
    }
    return 0;
}
        
