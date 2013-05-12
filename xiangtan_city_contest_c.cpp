#include<iostream>
#include<cstdio>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
#define MAX(a,b)((a)>(b)?(a):(b))
#define MIN(a,b)((a)<(b)?(a):(b))
#define N -1
#define M 1e11
using namespace std;
__int64 sum;
int mark;
int mmark;
struct node
{
    __int64 x;
    __int64 y;
    __int64 mm;
    __int64 mi;
    __int64 xxmi;
}s[100100];
__int64 q[200100];
node tree[200100<<2];
void build(int ll,int rr,int nn)
{
    int mid=(ll+rr)>>1;
    tree[nn].x=ll;
    tree[nn].y=rr;
    tree[nn].xxmi=M;
    tree[nn].mi=N;
    tree[nn].mm=0;
    if(ll==rr)return ;
    build(ll,mid,nn<<1);
    build(mid+1,rr,(nn<<1)+1);
}
int inse(int ll,int rr,int nn,int num,int next)
{
    int mid=(tree[nn].x+tree[nn].y)>>1;
    next=MAX(tree[nn].mi,next);
    if(num<tree[nn].mi)return 0;
    if(ll==tree[nn].x&&rr==tree[nn].y)
    {
       if(num>tree[nn].xxmi)return 0;
       if(tree[nn].mi==N||tree[nn].mi==num)
        {
            tree[nn].mi=num;
            if(num<=tree[nn].xxmi&&tree[nn].xxmi==M)
            {
            mark=1;
            __int64 tt=(q[tree[nn].y]-q[tree[nn].x]+1);
            tree[nn].mm+=tt*num;
            return (num-next)*tt;
            }
            else if(tree[nn].xxmi!=M&&num<=tree[nn].xxmi)
            {
                if(tree[nn].x==tree[nn].y)return 0;
                __int64 uu1=inse(ll,mid,nn<<1,num,next);
                __int64 uu2=inse(mid+1,rr,(nn<<1)+1,num,next);
                tree[nn].mm+=uu1+uu2;
                return uu1+uu2;
            }
            return 0;
        }
        return 0;
    }
    tree[nn].xxmi=MIN(tree[nn].xxmi,num);
    if(mid>=rr)
      {
        __int64 uu=inse(ll,rr,nn<<1,num,next);
        tree[nn].mm+=uu;
        return uu;
      }
    else if(mid<ll)
       {
           __int64 uu=inse(ll,rr,(nn<<1)+1,num,next);
           tree[nn].mm+=uu;
           return uu;
       }
    else
    {
        __int64 uu1=inse(ll,mid,nn<<1,num,next);
        __int64 uu2=inse(mid+1,rr,(nn<<1)+1,num,next);
        tree[nn].mm+=uu1;
        tree[nn].mm+=uu2;
        return uu1+uu2;
    }
    return 0;
}
int main()
{
    int i,j,m,n;
    scanf("%d",&n);
    while(n--)
    {
        sum=0;
        mark=0;
        mmark=0;
        vector<__int64> w;
        scanf("%d",&m);
        for(i=1;i<=m;i++)
           {
                scanf("%I64d%I64d%I64d",&s[i].x,&s[i].y,&s[i].mm);
                w.push_back(s[i].x);
                w.push_back(s[i].y);
           }
        sort(w.begin(),w.end());
        w.erase(unique(w.begin(),w.end()),w.end());
        #define FIND(v)(lower_bound(w.begin(),w.end(),v)-w.begin())
        build(1,w.size(),1);
        for(i=1;i<=m;i++)
        {
            mark=0;
            int xx=FIND(s[i].x)+1;
            int yy=FIND(s[i].y)+1;
            q[xx]=s[i].x;
            q[yy]=s[i].y;
            inse(xx,yy,1,s[i].mm,0);
            if(mark==0){mmark=1;break;}
        }
        if(mmark==1)printf("Error\n");
        else printf("%I64d\n",tree[1].mm);
        #undef FIND
    }
    return 0;
}
/*
wa data
5
5
1000 2000 6
1000 1500 10
1000 1001 15
1 2 1
2 3 1
*/
