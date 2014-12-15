#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#define maxn 110*3
#define maxe 50000
#define inf 1000000000
#define ll long long
using namespace std;

string s;

int main()
{
    freopen("input.txt","r",stdin);
    int i,j;
    cin>>s;
    for(i=0;i<s.size();i++)
    {
        if(s[i]=='M')
        {
            break;
        }
    }
    int pos;
    int ans=0;
    for(pos=i;i<s.size();i++)
    {
        if(s[i]=='F')
        {
            if(i-pos>ans)
            {
                ans=i-pos;
            }
            else
            {
                ans++;
            }
            pos++;
        }
    }
    cout<<ans<<endl;
}
