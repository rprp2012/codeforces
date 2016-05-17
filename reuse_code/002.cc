#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,m,_a[200101],_b[200101],_c[200101],_inf=10000000;
int start_a,start_b,start_len;
int num[30001],pre[30001],dis[30001],now[30001],his[30001];
struct Graph{
	int head[410001],next[410001],tob[410001],cc[410001],len;
	void Init() {
		memset(head,0,sizeof(head));
		memset(next,0,sizeof(next));
		memset(tob,0,sizeof(tob));
		memset(cc,0,sizeof(cc));
		len=1;
	}
	void Add(int u,int v,int w) {
		++len;next[len]=head[u];head[u]=len;tob[len]=v;cc[len]=w;
	}
}g;
int sap(int &ss,int &tt)
{
	bool flag;
	int aug=_inf,min,flow=0,u,v;
	memset(dis,0,sizeof(dis));
	memset(num,0,sizeof(num));
	num[0]=n;
	for (int i=1;i<=n;++i) 
		now[i]=g.head[i];
	u=ss;
	while (dis[ss]<=n)
	{
		his[u]=aug;
		flag=false;
		for (int j=now[u];j;j=g.next[j])
		{
			if (g.cc[j]>0&&((dis[g.tob[j]]+1)==dis[u]))
			{
				flag=true;
				pre[g.tob[j]]=j;
				now[u]=j;
				if (aug>g.cc[j]) aug=g.cc[j];
				u=g.tob[j];

				if (u==tt)
				{
					flow+=aug;
					for (;u!=ss;u=g.tob[pre[u]^1]) 
						g.cc[pre[u]]-=aug,g.cc[pre[u]^1]+=aug;
					aug=_inf;
				}
				break;
			}
		}
		if (flag) continue;
		min=n+1;
		v=0;
		for (int j=g.head[u];j;j=g.next[j]) 
			if (g.cc[j]>0&&dis[g.tob[j]]<min) min=dis[g.tob[j]],v=j;
		--num[dis[u]];
		if (num[dis[u]]==0) return flow;
		dis[u]=min+1;
		++num[dis[u]];
		now[u]=v;
		if (u!=ss) {u=g.tob[pre[u]^1];aug=his[u];}
	}
	return flow;
}
int main() {
	int tt;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i) {
		scanf("%d%d%d",&_a[i],&_b[i],&_c[i]);
		if (_a[i]>_b[i]) {tt=_a[i];_a[i]=_b[i];_b[i]=tt;}
	}
	scanf("%d%d%d",&start_a,&start_b,&start_len);
	if (start_a>start_b) {tt=start_a;start_a=start_b;start_b=tt;}
	g.Init();
	for (int i=1;i<=m;++i) 
		if (_c[i]<start_len) 
    	{
			g.Add(_a[i],_b[i],1);
			g.Add(_b[i],_a[i],1);
		} 
	int deta=sap(start_a,start_b);
	g.Init();
	for (int i=1;i<=m;++i) 
		if (_c[i]>start_len) {
			g.Add(_a[i],_b[i],1);
			g.Add(_b[i],_a[i],1);
		}
	deta+=sap(start_a,start_b);
	printf("%d\n",deta);
	return 0;
}
