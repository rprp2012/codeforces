#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
int n,m,Task,aa[510001],TT,Deta,Flag;
struct Graph{
	int l,r,sum,dc;
}Tree[2100001];
void Build(int u,int L,int R) {
	if (L==R) {
		Tree[u].l=Tree[u].r=aa[L];
		Tree[u].sum=1;return;
	}
	int Mid=(L+R)>>1,l=u<<1;
	int r=l+1;
	Build(l,L,Mid);
	Build(r,Mid+1,R);
	Tree[u].l=Tree[l].l;
	Tree[u].r=Tree[r].r;
	Tree[u].sum=Tree[l].sum+Tree[r].sum;
	if (Tree[l].r==Tree[r].l) --Tree[u].sum;
}
void Weihu(int u) {
	int l=u<<1;int r=l+1;
	Tree[l].dc=Tree[l].l=Tree[l].r=Tree[r].dc=Tree[r].l=Tree[r].r=Tree[u].dc;
	Tree[l].sum=Tree[r].sum=1;
	Tree[u].dc=0;
}
int Find(int u,int L,int R,int X) {
	if (L==R) return Tree[u].l;
	int Mid=(L+R)>>1;
	if (Tree[u].dc>0) Weihu(u);
	if (X<=Mid) return Find(u<<1,L,Mid,X); else 
		return Find((u<<1)+1,Mid+1,R,X);
}
void Change(int u,int L,int R,int ll,int rr,int xx) {
	if (L==ll&&R==rr) {
		Tree[u].l=Tree[u].r=xx;
		Tree[u].sum=1;Tree[u].dc=xx;
		return;
	}
	int Mid=(L+R)>>1,l=u<<1;
	int r=l+1;
	if (Tree[u].dc>0) Weihu(u);
	if (rr<=Mid) Change(l,L,Mid,ll,rr,xx); else 
	if (ll>Mid) Change(r,Mid+1,R,ll,rr,xx); else {
		Change(l,L,Mid,ll,Mid,xx);
		Change(r,Mid+1,R,Mid+1,rr,xx);
	}
	Tree[u].l=Tree[l].l;Tree[u].r=Tree[r].r;
	Tree[u].sum=Tree[l].sum+Tree[r].sum;
	if (Tree[l].r==Tree[r].l) --Tree[u].sum;
}
int Count(int u,int L,int R,int ll,int rr) {
//cout<<"-- "<<u<<" "<<L<<" "<<R<<" "<<ll<<" "<<rr<<" "<<Tree[u].sum<<endl;
	if (L==ll&&R==rr) return Tree[u].sum;
	int Mid=(L+R)>>1,l=u<<1;
	int r=l+1;
	if (Tree[u].dc>0) Weihu(u);
	if (rr<=Mid) return Count(l,L,Mid,ll,rr); else 
	if (ll>Mid) return Count(r,Mid+1,R,ll,rr); else {
		int tmp=Count(l,L,Mid,ll,Mid)+Count(r,Mid+1,R,Mid+1,rr);
		if (Tree[l].r==Tree[r].l) --tmp;
		return tmp;
	}
}
int main() {
	char cc;
	int XX,YY,ZZ,_x,_y,Ans;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) 
		scanf("%d",&aa[i]);
	
	memset(Tree,0,sizeof(Tree));
    Build(1,1,n);

	Deta=0;Flag=1;
	scanf("%d",&Task);
	for (int ppp=1;ppp<=Task;++ppp) {
		cc=getchar();
		while (cc!='R'&&cc!='F'&&cc!='S'&&cc!='P'&&cc!='C') cc=getchar();
		if (cc=='R') {
			scanf("%d",&XX);
			Deta-=(Flag*XX);
			Deta%=n;
		} else 
		if (cc=='F') {
			Deta+=(Flag*(n+2));
			Deta%=n;
			Flag=-Flag;
		} else 
		if (cc=='S') {
			scanf("%d%d",&_x,&_y);
			_x=Deta+Flag*_x;_x%=n;while (_x<=0) _x+=n;
			_y=Deta+Flag*_y;_y%=n;while (_y<=0) _y+=n;
			XX=Find(1,1,n,_x);YY=Find(1,1,n,_y);
			Change(1,1,n,_x,_x,YY);
			Change(1,1,n,_y,_y,XX);
		} else 
		if (cc=='P') {
			scanf("%d%d%d",&XX,&YY,&ZZ);
			XX=Deta+Flag*XX;XX%=n;while (XX<=0) XX+=n;
			YY=Deta+Flag*YY;YY%=n;while (YY<=0) YY+=n;
//cout<<XX<<" "<<YY<<" "<<ZZ<<endl;
			if (Flag==1) {
				if (XX<=YY) Change(1,1,n,XX,YY,ZZ); else 
					Change(1,1,n,1,YY,ZZ),Change(1,1,n,XX,n,ZZ);
			} else {
				if (YY<=XX) Change(1,1,n,YY,XX,ZZ); else 
					Change(1,1,n,1,XX,ZZ),Change(1,1,n,YY,n,ZZ);
			}
		} else {
			cc=getchar();
			if (cc=='S') {
				scanf("%d%d",&XX,&YY);
				XX=Deta+Flag*XX;XX%=n;while (XX<=0) XX+=n;
				YY=Deta+Flag*YY;YY%=n;while (YY<=0) YY+=n;
//cout<<XX<<" "<<YY<<" "<<Deta<<" "<<Flag<<endl;
				Ans=0;
				if (Flag==1) {
					if (XX<=YY) Ans=Count(1,1,n,XX,YY); else {
						Ans=Count(1,1,n,1,YY)+Count(1,1,n,XX,n);
						if (Tree[1].r==Tree[1].l) --Ans;
					}
				} else {
					if (YY<=XX) Ans=Count(1,1,n,YY,XX); else {
						Ans=Count(1,1,n,1,XX)+Count(1,1,n,YY,n);
						if (Tree[1].l==Tree[1].r) --Ans;
					}
				}
				printf("%d\n",Ans);
			} else {
				XX=Tree[1].sum;
				if (Tree[1].l==Tree[1].r) --XX;
				if (XX==0) XX=1;
				printf("%d\n",XX);
			}
		}
	}
	return 0;
}
