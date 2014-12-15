#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stdlib.h>
#define N 10010
using namespace std;
int n,m;
struct splaytree
{
    int size[N],ch[N][2],f[N],va[N];
    int root,top;
    inline void zig(int x)
    {
        int y = f[x],z = f[y];
        ch[y][1] = ch[x][0];f[ch[x][0]] = y;
        f[x] = z;ch[x][0] = y;f[y] = x;
        if(z) ch[z][ch[z][1]==y] = x;
        pushup(y);
    }
    inline void zag(int x)
    {
        int y = f[x],z = f[y];
        ch[y][0] = ch[x][1];f[ch[x][1]] = y;
        ch[x][1] = y;f[y] = x;f[x] = z;
        if(z) ch[z][ch[z][1]==y] = x;
        pushup(y);
    }
    inline void zigzig(int x)
    {
        int y = f[x],z = f[y],fz = f[z];
        ch[z][1] = ch[y][0]; f[ch[y][0]] = z;
        ch[y][1] = ch[x][0]; f[ch[x][0]] = y;
        f[z] = y;ch[y][0] = z;
        f[y] = x;ch[x][0] = y;
        f[x] = fz;
        if(fz) ch[fz][ch[fz][1]==z] = x;
        pushup(z);pushup(y);
    }
   inline void zagzag(int x){

        int y=f[x], z=f[y], fz=f[z];

        ch[z][0]=ch[y][1]; f[ch[y][1]]=z;

        ch[y][0]=ch[x][1]; f[ch[x][1]]=y;

        f[z] = y;ch[y][1] = z;
        f[y] = x;ch[x][1] = y;
        f[x] = fz;
        if(fz) ch[fz][ch[fz][1]==z] = x;
        pushup(z);pushup(y);
    }
    inline void zigzag(int x)
    {
        int y = f[x],z = f[y],fz = f[z];
        ch[y][1] = ch[x][0] ; f[ch[x][0]] = y;
        ch[z][0] = ch[x][1] ; f[ch[x][1]] = z;
        f[z] = x;ch[x][0] = y;
        f[y] = x;ch[x][1] = z;
        f[x] = fz;
        if(fz) ch[fz][ch[fz][1]==z] = x;
        pushup(y);pushup(z);
    }
    inline void zagzig(int x)
    {
        int y = f[x],z = f[y],fz = f[z];
        ch[y][0] = ch[x][1] ; f[ch[x][1]] = y;
        ch[z][1] = ch[x][0] ; f[ch[x][0]] = z;
        f[z] = x;ch[x][0] = z;
        f[y] = x;ch[x][1] = y;
        f[x] = fz;
        if(fz) ch[fz][ch[fz][1]==z] = x;
        pushup(y);pushup(z);
    }
    void splay(int x,int goal)
    {
        int y,z;
        while(f[x]!=goal)
        {
            if(f[f[x]]==goal)
            {
                y = f[x];
                if(ch[y][1]==x)
                zig(x);
                else
                zag(x);
            }
            else
            {
                y = f[x];z =f[y];
                if(ch[z][1]==y)
                {
                    if(ch[y][1]==x)
                    zigzig(x);
                    else
                    zagzig(x);
                }
                else
                {
                    if(ch[y][0]==x)
                    zagzag(x);
                    else
                    zigzag(x);
                }
            }
        }
        pushup(x);
        if(f[x]==0)
        root = x;
    }
    inline void pushup(int x)
    {
        size[x] = size[ch[x][0]]+size[ch[x][1]]+1;
    }
    void init()
    {
        size[0] = ch[0][1] = ch[0][0] = f[0] = root = va[0] = top = 0;
//        insert(1000000001);
    }
    inline int newnode(int v)
    {
        size[++top] = 1;
        ch[top][0] = ch[top][1] = f[top] = 0;
        va[top] = v;
        return top;
    }
    void insert(int v)
    {
        int r = root,x;
        for(;;)
        {
            if(v>=va[r])
            {
                if(ch[r][1])
                r = ch[r][1];
                else
                {
                    x = newnode(v);
                    ch[r][1] = x;
                    f[x] = r;
                    break;
                }
            }
            else
            {
                if(ch[r][0])
                r = ch[r][0];
                else
                {
                    x = newnode(v);
                    ch[r][0] = x;
                    f[x] = r;
                    break;
                }
            }
        }
        splay(x,0);
    }
    int query(int v)
    {
        if (root == 0) {
            return v;
        }
        int r = root,k = v,res = size[ch[root][0]];
        for(;;)
        {
            if(k<va[r]-res)
            {
                if(ch[r][0])
                {
                    r = ch[r][0];
                    res -= size[ch[r][1]]+1;
                }
                else
                {
                    splay(r,0);
                    return k+res;
                }
            }
            else
            {
                if(ch[r][1])
                {
                    r = ch[r][1];
                    res += 1+size[ch[r][0]];
                }
                else
                {
                    splay(r,0);
                    return k + res + 1;
                }
            }
        }
    }
}tree;
int main()
{
//    freopen("in.txt", "r", stdin);
    int k;
    char s[5];
    tree.init();
    scanf("%d%d",&n,&m);
    while(m--)
    {
        scanf("%s%d",s,&k);
        if(s[0]=='L')
        printf("%d\n",tree.query(k));
        else
        {
            int x = tree.query(k);
            tree.insert(x);
        }
    }
    return 0;
}
