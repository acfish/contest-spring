#include<iostream>
#include<cstdio>
#include<cstring>

#define MAX(a,b)((a)>(b)?(a):(b))
using namespace std;

const int MAXN=1e4;
int pp[110][110];
int next[110][110];
int dp[110][310];
int vp[110];
int cp[110];
void floyd(int nn)
{
    for(int ii=0;ii<nn;ii++)
    {
        for(int jj=0;jj<nn;jj++)
        {
            for(int kk=0;kk<nn;kk++)
                pp[ii][jj]=min(pp[ii][kk]+pp[kk][jj],pp[ii][jj]);
        }
    }
    return ;
}
void init(int nn,int tt)
{
    for(int ii=0;ii<nn;ii++)
    {
        pp[ii][ii]=0;
        for(int jj=0;jj<nn;jj++)
        {
            if(ii==jj)continue;
            pp[ii][jj]=MAXN;
        }
    }
    memset(next,0,sizeof(next));
    for(int ii=0;ii<nn;ii++)
    {
        for(int jj=0;jj<=tt;jj++)
        {
            dp[ii][jj]=-MAXN;
        }
    }
    return ;
}
int main()
{
    int i,j,m,n,s,t,e,w;
    scanf("%d",&w);
    for(int kk=1;kk<=w;kk++)
    {
        scanf("%d%d%d%d%d",&n,&m,&t,&s,&e);
        init(n,t);
        for(i=0;i<n;i++)
            scanf("%d",&cp[i]);
        for(i=0;i<n;i++)
            scanf("%d",&vp[i]);
        for(i=1;i<=m;i++)
        {
            int a,c,b;
            scanf("%d%d%d",&a,&b,&c);
            pp[a][b]=c;
            pp[b][a]=c;
            next[a][++next[a][0]]=b;
            next[b][++next[b][0]]=a;
        }
        floyd(n);
        dp[s][0]=0;
        dp[s][cp[s]]=vp[s];
        int get_tt=-MAXN;
        for(int v=0;v<n;v++)
        {
           for(i=0;i<n;i++)
          {
            for(j=0;j<=t;j++)
            {
                for(int k=1;k<=next[i][0];k++)
                {
                    int ee=next[i][k];
                    if(j-cp[i]-pp[i][ee]<0)continue;
                    dp[i][j]=max(dp[ee][j-cp[i]-pp[i][ee]]+vp[i],dp[i][j]);
                }
            }
          }
        }
        int get_max=-MAXN;
        for(i=t;i>=0;i--)
            get_max=max(dp[e][i],get_max);
        for(i=0;i<n;i++)
        {
            for(j=t-pp[i][e];j>=0;j--)
            get_max=max(get_max,dp[i][j]);
        }
        printf("Case #%d:\n",kk);
        printf("%d\n",get_max);
    }
    return 0;
}
/*
not ac
*/
