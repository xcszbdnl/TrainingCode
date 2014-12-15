
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
#define MAXN 28

bool adj[MAXN][MAXN];
int in_degree[MAXN];
char str[MAXN];
int n,m;

int topo_sort()
{
    int i,j,k;
    bool flag=true;
    memset(in_degree,0,sizeof(in_degree));
    memset(str,'\0',sizeof(str));
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
            if(adj[i][j])
                in_degree[j]++; //入度加一
    }
    for(i=1; i<=n; i++)  //每次产生一个字符
    {
        k=0;
        for(j=1; j<=n; j++)
        {
            if(in_degree[j]==0)
            {
                if(k==0) k=j;
                else {flag=false;
                    break;
                }//还有入度为零的节点
            }
        }
        if(k==0) return 0; //没有入度为零的节点，即存在环
        in_degree[k]=-1;
        str[i-1]=k+'A'-1;
        for(j=1; j<=n; j++)  //k指向的节点入度都减一，即去掉A及它相关的边
        {
            if(adj[k][j])
                in_degree[j]--;
        }
    }
    if(flag) return 1;  //没有入度为零的点，完成排序
    else return 2;     //排序没有完成
}

int main()
{
    int i,a,b,result;
    char s[4];

    while(scanf("%d%d",&n,&m),m+n)
    {
        memset(adj,false,sizeof(adj));
        bool h=false;
        for(i=1; i<=m; i++)
        {
            scanf("%s",s);
            a=s[0]-'A'+1; b=s[2]-'A'+1;
            adj[a][b]=true;
            if(h) continue;   //必须有，因为还要继续把剩下的数据都读完
                        result=topo_sort();
            if(result==1)
            {
                printf("Sorted sequence determined after %d relations: %s.\n",i,str);
                h=true;
            }
            if(result==0)
            {
                printf("Inconsistency found after %d relations.\n",i);   //有换存在
                h=true;
            }
        }
        if(!h) printf("Sorted sequence cannot be determined.\n");
    }
    return 0;
}
