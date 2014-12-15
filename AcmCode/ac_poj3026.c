 
    /*BFS+Prim*/  
      
    //Memory Time   
    //368K   0MS   
      
    #include<iostream>  
#include <string.h>
    #include<string>  
#include <stdio.h>
    using namespace std;  
      
    const int inf=2501;      //无限大,最大迷宫的总长也就2500  
      
    char map[51][51];  //迷宫原图  
    int node[51][51];   //记录当前格是否为字母，是第几个字母  
    int col,row;      //当前迷宫的行列数  
    int num;         //字母顶点数数目  
    int dist[102][102];      //构造结点图的两结点间权值，理论结点数最多为2500个（每一个允许通行的格为一个结点）  
                             //但是POJ的数据库允许压缩到101个，哈哈，这样时间和空间复杂度都减少很多  
    int edge[102][102];      //构造字母图的两个字母间的边权，字母数最多为101  
      
    class move  
    {  
     public:  
        int row,col;  
    }mov[4]={{0,-1},{0,1},{-1,0},{1,0}}; //分别对应 上 下 左 右  
      
    void bfs(int i,int j)  
    {  
        bool vist[51][51];  //标记当前迷宫某一格是否已被访问  
        int que_x[2500],que_y[2500];  //坐标队列  
        int head=0,tail=0;  //队列指针  
      
        /*Initial*/  
      
        memset(dist,0,sizeof(dist));  
        memset(vist,false,sizeof(vist));  
        vist[i][j]=true;  
        que_x[tail]=i;  
        que_y[tail++]=j;  
      
        while(head<tail)  
        {  
            int x=que_x[head];  
            int y=que_y[head++];  
            if(node[x][y])  
                edge[ node[i][j] ][ node[x][y] ] = dist[x][y];   //抽取字母到字母的边权  
            for(int k=0;k<4;k++)  
            {  
                int mx=x+mov[k].row;  
                int my=y+mov[k].col;  
                if(mx>=1 && mx<= row && my>=1 && my<=col)  
                    if(!vist[mx][my] && map[mx][my]!='#')  
                    {  
                        que_x[tail]=mx;  
                        que_y[tail++]=my;  
                        vist[mx][my]=true;  
                        dist[mx][my]=dist[x][y]+1;  
                    }  
            }  
        }  
        return;  
    }  
      
    int prim(void)  
    {  
        int s=1;  
        int m=1;  
        bool u[102];  
        u[s]=true;  
      
        int min_w;  
        int prim_w=0;  
        int point;  
        int low_dis[102];  
      
        for(int i=1;i<=num;i++)  
        {  
            low_dis[i]=inf;  
            u[i]=false;  
        }  
      
        while(true)  
        {  
            if(m==num)  
                break;  
      
            min_w=inf;  
            for(int i=2;i<=num;i++)  
            {  
                if(!u[i] && low_dis[i]>edge[s][i])  
                    low_dis[i] = edge[s][i];  
                if(!u[i] && min_w>low_dis[i])  
                {  
                    min_w=low_dis[i];  
                    point=i;  
                }  
            }  
            s=point;  
            u[s]=true;  
            prim_w+=min_w;  
            m++;  
        }  
        return prim_w;  
    }  
      
    int main()  
    {  
      freopen("input.txt", "r", stdin);
int test, i, j;  
        cin>>test;  
        while(test--)  
        {  
            /*Initial*/  
      
            memset(node,0,sizeof(node));  
            num=0;  
      
            /*Input*/  
      
            cin>>col>>row;  
            char temp[51];  
            gets(temp);  //吃掉cin遗留下来的换行符,我不知道为什么getchar()会AW  
            for( i=1;i<=row;i++)  
            {  
                gets(map[i]);  
                for( j=1;j<=col;j++)  
                    if(map[i][j]=='A'||map[i][j]=='S')  
                        node[i][j]=++num;  
            }  
      
            /*BFS-> Structure Maps*/  
      
            for(i=1;i<=row;i++)  
                for(j=1;j<=col;j++)  
                    if(node[i][j])  
                        bfs(i,j);   //构造结点i,j到其他所有结点的边权（非#的格子就是一个结点）  
      
            /*Prim Algorithm & Output*/  
      
            cout<<prim()<<endl;  
        }  
        return 0;  
    }  
