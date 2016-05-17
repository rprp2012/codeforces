#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;
const int INF=10000;
int n,m;
struct Bignum
{
	int dat[3000],len;
	void init(int u)
	{
		memset(dat,0,sizeof(dat));
		int i;
		for (len=5,dat[1]=u,i=1;i<=len;++i)
			if (dat[i]>=INF)
			{
				dat[i+1]+=dat[i]/INF;
				dat[i]%=INF;
			} else break;
		for (;dat[len]==0&&len>1;--len);
	}
	void operator -=(const Bignum &u)
	{
		int i;
		for (i=1;i<=u.len;++i)
			dat[i]-=u.dat[i];
		for (i=1;i<=len;++i)
			for (;dat[i]<0;dat[i]+=INF,--dat[i+1]);
		for (;dat[len]==0&&len>1;--len);
	}
	void operator *=(const int &deta)
	{
		int i;
		for (i=1;i<=len;++i)
			dat[i]*=deta;
		for (len+=3,i=1;i<=len;++i)
			if (dat[i]>=INF)
			{
				dat[i+1]+=dat[i]/INF;
				dat[i]%=INF;
			}
		for (;dat[len]==0&&len>1;--len);
	}
	void print()
	{
		printf("%d",dat[len]);
		for (int i=len-1;i>0;--i)
		{
			if (dat[i]<10) printf("000"); else
			if (dat[i]<100) printf("00"); else
			if (dat[i]<1000) printf("0");
			printf("%d",dat[i]);
		}
		puts("");
	}
};
Bignum ta,tb;
int main()
{
	int i;
	freopen("queue.in","r",stdin);
	freopen("queue.out","w",stdout);
	scanf("%d%d",&n,&m);
	ta.init((n+2)*(n+1));
	tb.init(2*n+2);
	for (i=0;i<m;++i)
	{
		ta*=n+3-i;
		tb*=n+2-i;
	}
	ta-=tb;
	for (i=2;i<=n;++i)
		ta*=i;
	ta.print();
	return 0;
}
