#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,m,Dfn[11001],Low[11001],Stack[11001],Top,Tim,Base[11001],Father[11001];
int _a[11001],_b[11001],Du[11001];
bool _c[11001];
struct Graph{
	int head[21001],next[21001],tob[21001],no[21001],len;
	void Init() {
		memset(head,0,sizeof(head));
		memset(next,0,sizeof(next));
		memset(tob,0,sizeof(tob));
		memset(no,0,sizeof(no));
		len=0;
	}
	void Add(int u,int v,int w) {
		++len;next[len]=head[u];head[u]=len;tob[len]=v;no[len]=w;
	}
}g;
void Tj(int u) {
	++Tim;
	Dfn[u]=Low[u]=Tim;
	++Top;
	Stack[Top]=u;
	for (int j=g.head[u];j;j=g.next[j]) 
		if (g.tob[j]!=Father[u]) {
			if (Dfn[g.tob[j]]==0) {
				Father[g.tob[j]]=u;
				Tj(g.tob[j]);
				if (Low[g.tob[j]]<Low[u]) Low[u]=Low[g.tob[j]];
				if (Low[g.tob[j]]>Dfn[u]) _c[g.no[j]]=1;
			} else 
			if (Dfn[g.tob[j]]>0) {
				if (Dfn[g.tob[j]]<Low[u]) Low[u]=Dfn[g.tob[j]];
			}
		}
	if (Dfn[u]==Low[u]) {
		Base[u]=u;Dfn[u]=-1;
		for (;Stack[Top]!=u;--Top) {
			Base[Stack[Top]]=u;
			Dfn[Stack[Top]]=-1;
		}
		--Top;
	}
}
int main() {
	g.Init();
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i) {
		scanf("%d%d",&_a[i],&_b[i]);
		g.Add(_a[i],_b[i],i);g.Add(_b[i],_a[i],i);
	}
	memset(Dfn,0,sizeof(Dfn));
	memset(Low,0,sizeof(Low));
	memset(Father,0,sizeof(Father));
	memset(_c,0,sizeof(_c));
	for (int i=1;i<=n;++i)
		if (Dfn[i]==0) {Top=0;Tim=0;Tj(i);}
	
	g.Init();
	for (int i=1;i<=m;++i) 
		if (_c[i]==0) g.Add(_a[i],_b[i],0),g.Add(_b[i],_a[i],0);
	memset(Dfn,0,sizeof(Dfn));
	memset(Low,0,sizeof(Low));
	memset(Father,0,sizeof(Father));
	for (int i=1;i<=n;++i)
		if (Dfn[i]==0) {Top=0;Tim=0;Tj(i);}
	
	memset(Du,0,sizeof(Du));
	for (int i=1;i<=m;++i) 
		if ((_c[i]==1)&&Base[_a[i]]!=Base[_b[i]]) ++Du[Base[_a[i]]],++Du[Base[_b[i]]];
	
	int Ans=0;
	for (int i=1;i<=n;++i) 
		if (Du[Base[i]]==1) {Ans++;Du[Base[i]]=0;}
	cout<<((Ans+1)/2)<<endl;
	return 0;
}
