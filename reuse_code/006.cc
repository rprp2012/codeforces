#include<cstdio>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int n,m,tmp[10001];
double PI=3.1415926,_inf=1e-6;
struct Complex{
	double a,b;
}aa[10001],bb[10001],cc[10001],dd[10001];
void Init() {
	memset(aa,0,sizeof(aa));
	memset(bb,0,sizeof(bb));
	memset(cc,0,sizeof(cc));
	memset(dd,0,sizeof(dd));
	char cc;
	for (n=0;;) {
		cc=getchar();
		if (cc>='0'&&cc<='9') {++n;aa[n].a=cc-48;} else break;
	}
	for (m=0;;) {
		cc=getchar();
		if (cc>='0'&&cc<='9') {++m;bb[m].a=cc-48;} else break;
	}
	
	int p=n/2;Complex tt;
	for (int i=1;i<=p;++i) {
		tt=aa[i];aa[i]=aa[n-i+1];aa[n-i+1]=tt;
	}
	for (int i=1;i<=n;++i)
		aa[i-1]=aa[i];
	aa[n].a=aa[n].b=0;
	p=m/2;
	for (int i=1;i<=p;++i) {
		tt=bb[i];bb[i]=bb[m-i+1];bb[m-i+1]=tt;
	}
	for (int i=1;i<=m;++i)
		bb[i-1]=bb[i];
	bb[m].a=bb[m].b=0;
	if (n<m) n=m;
	n<<=1;
	int tmp;
	for (tmp=1;tmp<n;tmp<<=1);
	n=tmp;
}
inline Complex operator * (Complex u,Complex v) {
	Complex w;
	w.a=u.a*v.a-u.b*v.b;
	w.b=u.b*v.a+u.a*v.b;
	return w;
}
inline Complex operator + (Complex u,Complex v) {
	Complex w;
	w.a=u.a+v.a;
	w.b=u.b+v.b;
	return w;
}
inline Complex operator - (Complex u,Complex v) {
	Complex w;
	w.a=u.a-v.a;
	w.b=u.b-v.b;
	return w;
}
inline int rev(int u,int n) {
	int v=0;
	for (n>>=1;n;u>>=1,n>>=1) {
		v<<=1;
		v|=(u&1);
	}
	return v;
}
void FFT(int n,double Theta,Complex A[],Complex Y[]) {
	Complex w,wn;
	for (int i=0;i<n;++i)
		Y[rev(i,n)]=A[i];
	for (int deta=2,mh=1;deta<=n;deta<<=1,mh<<=1) {
		for (int j=0;j<n;j+=deta) {
			w.a=1;w.b=0;
			wn.a=cos(Theta/deta );
			wn.b=sin(Theta/deta);
			for (int k=0;k<mh;++k) {
				Complex u=Y[j+k],tt=w*Y[j+k+mh];
				Y[j+k]=u+tt;
				Y[j+k+mh]=u-tt;
				w=w*wn;
			}
		}
	}
}
int main() {
	Init();
	FFT(n,2*PI,aa,cc);
	FFT(n,2*PI,bb,dd);
	for (int i=0;i<n;++i)
		cc[i]=cc[i]*dd[i];
	FFT(n,-2*PI,cc,dd);

	for (int i=n-1;i>=0;--i) 
		tmp[i]=int(dd[i].a/n+_inf);
	for (int i=0;i<=n;++i) {
		tmp[i+1]+=(tmp[i]/10);
		tmp[i]%=10;
	}
	while (tmp[n]==0&&n) --n;
	for (int i=n;i>=0;--i)
		cout<<tmp[i];
	cout<<endl;
	return 0;
}
