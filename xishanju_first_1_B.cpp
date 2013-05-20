#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<map>
#include<cmath>
#include<vector>
using namespace std;

const int MAXN=100100;

vector<int>son[MAXN];
map<string,int> change;
int ee[MAXN];
int dd[MAXN];
int mark[MAXN];
int dp[100100<<1][20];
int deep[100100<<1];
int sta,top;
void dfs(int nn,int hh)
{
    ee[nn]=top;
    deep[top++]=hh;
    dd[nn]=hh;
    for(int ii=0;ii<son[nn].size();ii++)
    {
        dfs(son[nn][ii],hh+1);
        deep[top++]=hh;
    }
    return ;
}//在线的求lca

double get_limit(int nn)
{
    return log(nn*1.0)/log(2.0);
}

void rmq()
{
    int rr=(int)get_limit(top);
    for(int ii=0;ii<top;ii++)
    dp[ii][0]=deep[ii];
    for(int jj=1;jj<=rr;jj++)
    {
        for(int ii=0;ii<top;ii++)
        {
            if(ii+(1<<jj)-1>top)break;
            dp[ii][jj]=min(dp[ii][jj-1],dp[ii+(1<<(jj-1))][jj-1]);
        }
    }
    return ;
}//用rmq求区间最值

int get_ans(int a1,int b1)
{
    if(a1>b1)swap(a1,b1);
    int len=b1-a1+1;
    int rr=(int)get_limit(len);
    return min(dp[a1][rr],dp[b1-(1<<rr)+1][rr]);
}

void init(int nn)
{
    change.clear();
    for(int ii=1;ii<=nn;ii++)
        son[ii].clear();
    return ;
}
int main()
{
    int i,j,m,n;
    scanf("%d",&n);
    while(n--)
    {
        memset(dp,0,sizeof(dp));
        memset(deep,0,sizeof(deep));
        int a,b;
        sta=0;
        top=0;
        scanf("%d%d",&a,&b);
        init(a);
        int step=1;
        for(i=1;i<=a-1;i++)
        {
            char aa[50],bb[50];
            scanf("%s%s",aa,bb);
            if(!change[aa])change[aa]=step++;
            if(!change[bb])change[bb]=step++;
            son[change[bb]].push_back(change[aa]);
            mark[change[aa]]=1;
        }
        for(i=1;i<step;i++)
        {
            if(!mark[i])
            {
                dfs(i,0);
                break;
            }
        }
        rmq();
        for(i=1;i<=b;i++)
        {
            char aa[50],bb[50];
            scanf("%s%s",aa,bb);
            if(change[aa]==change[bb])
            {
                printf("0\n");
                continue;
            }
            if(a==1)
            {
                printf("1\n");
                continue;
            }
            int lc=get_ans(ee[change[aa]],ee[change[bb]]);
            if(lc!=dd[change[bb]])
                printf("%d\n",(dd[change[aa]]-lc)+1);
            else
                printf("%d\n",(dd[change[aa]]-lc));
        }
    }
    return 0;
}
/*
我发现我有时挺傻逼的，它给的是string，我就一直用到死，感觉自己脑袋好僵的。
首先，就是在线的lca问题；
在线的lca：
用欧拉环游的方式dfs，求得每个点的遍历顺序，和对应的深度值，也要记录每个点的第一次遍历时的位置。
然后求lcd的方式，就是在那个区间（最先出现的位置）里面找深度最小的，则这个点所对应的值就是lcd；
然后就转化为区间求极值问题：
用rmq；
就是用dp[i][j]表示i->i+2^j-1的区间范围。
而如果要求出[a,b]的极值的话，就要算出最大的j值。
由于间距最少为1，所以对于相等的情况要另外讨论。
对于间距length=（b-a+1）。
指数n=（int）log2（length）；
那么j就是取n。
很明显，这是最接近b的最大的j；
对于动态转移方程的理解：
dp[i][j]=min(dp[i][j-1],do[i+2^(j-1)+1][j-1]);
开始的时候看傻眼了，怎么转化。。。
其实不要局限与i，由于之前担心i的初始化，其实可以用j啊。
要灵活！！！！
*/

