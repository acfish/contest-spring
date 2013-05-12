#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cmath>

#define eps 1e-8
#define N 1000000
#define MIN(a,b)((a)<(b)?(a):(b))
#define MAX(a,b)((a)>(b)?(a):(b))
#define abbs(a,b)((a-b)>0?(a-b):(b-a))
using namespace std;
double x1,x2,y11,y22,vr,vt;
double getxtt(double xx)
{
    return sqrt((xx-x1)*(xx-x1)+y11*y11)/(vr*1.0)+sqrt((xx-x2)*(xx-x2)+y22*y22)/(vt*1.0);
}
int main()
{
    int i,j,m,n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%lf%lf%lf%lf%lf%lf",&x1,&y11,&x2,&y22,&vr,&vt);
        double mid,midmid;
        double getxmin,getxmax;
        getxmin=MIN(x1,x2);
        getxmax=MAX(x1,x2);
        double ans=sqrt((x1-x2)*(x1-x2)*1.0+(y11-y22)*(y11-y22)*1.0)/(vr*1.0);
       // cout<<ans<<endl;
        double get1,get2;
        get1=N*1.0;
        get2=N*1.0;
        ans=MIN(ans,getxtt(x1));
        while(getxmin+eps<getxmax)
        {
            mid=(getxmin+getxmax)*1.0/2.0;
            midmid=(mid+getxmax)*1.0/2.0;
            get1=getxtt(mid);
            get2=getxtt(midmid);
           // cout<<get1<<' '<<get2<<endl;
            if(get1<get2)getxmax=midmid;
            else getxmin=mid;
        }
        ans=MIN(ans,get1);
        printf("%.2f\n",ans+eps);
    }
    return 0;
}
