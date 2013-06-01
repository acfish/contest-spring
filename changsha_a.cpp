#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
__int64 ans[3][3];
__int64 mm[3];
__int64 mark[3][3];
__int64 ww[3][3];
void init(__int64 ff1,__int64 ff2)
{
    memset(ans,0,sizeof(ans));
    for(int ii=1;ii<=2;ii++)
        ans[ii][ii]=1;
    mm[1]=ff2;
    mm[2]=ff1;
    memset(mark,0,sizeof(mark));
    return ;
}
void binary(int nn,int mo)
{
    while(nn)
    {
    if(nn&1)
    {
        memset(ww,0,sizeof(ww));
        for(int ii=1;ii<=2;ii++)
        {
            for(int jj=1;jj<=2;jj++)
            {
                for(int kk=1;kk<=2;kk++)
                {
                    ww[ii][jj]=(ww[ii][jj]+((ans[ii][kk]%mo)*(mark[kk][jj]%mo)%mo))%mo;
                }
            }
        }
        for(int ii=1;ii<=2;ii++)
            for(int jj=1;jj<=2;jj++)
            ans[ii][jj]=ww[ii][jj]%mo;
    }
    nn=nn>>1;
    memset(ww,0,sizeof(ww));
    for(int ii=1;ii<=2;ii++)
    {
        for(int jj=1;jj<=2;jj++)
        {
            for(int kk=1;kk<=2;kk++)
            {
                ww[ii][jj]=(ww[ii][jj]+((mark[ii][kk]%mo)*(mark[kk][jj]%mo)%mo))%mo;
            }
        }
    }
    for(int ii=1;ii<=2;ii++)
        for(int jj=1;jj<=2;jj++)
        mark[ii][jj]=ww[ii][jj]%mo;
    }
    return ;
}
__int64 get_ans(int nn,int mo)
{
    binary(nn,mo);
    __int64 uu=0;
    for(int ii=1;ii<=2;ii++)
        uu=(uu+(ans[ii][1]%mo)*(mm[ii]%mo))%mo;
    return uu%mo;
}
int main()
{
    int i,j,n,m;
    int a,b;
    while(scanf("%d%d%d%d",&a,&b,&n,&m)!=EOF)
    {

        __int64 f1=((int)ceil((a*1.0+sqrt(b*1.0))))%m;
        __int64 f2=((__int64)ceil((a*1.0+sqrt(b*1.0))*(a*1.0+sqrt(b*1.0))))%m;
        init(f1,f2);
        mark[1][1]=(2*(a%m))%m;
        mark[2][1]=((b-(a%m)*(a%m))%m+m)%m;
        mark[1][2]=1;
        mark[2][2]=0;
        __int64 tt;
        if(n==1)
            tt=f1;
        else if(n==2)
            tt=f2;
        else
            tt=get_ans(n-2,m);
        printf("%I64d\n",tt);
    }
    return 0;
}
/*
数据有可能爆int，所以要用__int64,比如求s2中。


运用组合数学中的递推关系；
由f(n)=a*f(n-1)+b*f(n-2);
能够得到f(n)=a1*(x1)^n+a2*(x2)^n（一般形式）
*/
