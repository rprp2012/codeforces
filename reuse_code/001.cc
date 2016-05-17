template <class T>
void Read(T &u) {
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar());
	u=0;
	for (;ch>='0'&&ch<='9';ch=getchar()) 
		u=u*10+ch-48;
}
void K_kmp() {
	int v,lmax,j;
	memset(_max,0,sizeof(_max));
	v=lmax=0;
	for (int i=2;i<=n;++i) {
		j=_max[i-v+1];
		if ((i+j-1)>lmax) j=lmax-i+1;
		if (j<0) j=0;
		for (;((i+j)<=n)&&(aa[i+j]==aa[1+j]);++j);
		_max[i]=j;
		if ((i+j)>lmax) v=i,lmax=i+j-1;
	}
	_max[1]=n;
}
