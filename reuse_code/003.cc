//  旅行商问题
//
//  模拟退火算法
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>

const double eps=1e-6;
struct City
{
	double x,y;
	char name[20];
}citys[50];
struct Seqce
{
	int dat[50];
	double f;
	void swap(int, int);
	void update();
	void print();
}current;

int n;
double Dis[55][55];

void work_tsp();
int main(int argc, char** argv)
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);

	srand(std::time(NULL));

	scanf("%d",&n);
	for (int i=1;i<=n;++i)		
		scanf("%s%lf%lf",citys[i].name,&citys[i].x,&citys[i].y);

	//  预先计算出任意两个城市间的距离
	for (int i=1;i<=n;++i)
		for (int j=1;j<=i;++j)
			Dis[i][j]=Dis[j][i]=sqrt((citys[i].x-citys[j].x)*(citys[i].x-citys[j].x)+(citys[i].y-citys[j].y)*(citys[i].y-citys[j].y));

	work_tsp();

	current.print();
	return 0;
}

void Seqce::swap(int p, int q)
{
	if (p == q) return;
	dat[p]^=dat[q];
	dat[q]^=dat[p];
	dat[p]^=dat[q];
	update();
}
void Seqce::update()
{
	f=Dis[dat[0]][dat[n-1]];
	for (int i=1;i<n;++i)
		f+=Dis[dat[i-1]][dat[i]];
}
void Seqce::print()
{
	for (int i=0;i<n;++i)
		printf("%s ",citys[dat[i]].name);
	printf("%.5lf\n",f);
}
void work_tsp()
{
	//  降温系数 r
	double r=0.998;
	//  起始温度 t
	double t=100;
	//  同一温度内的迭代次数 L
	double L=100*n;
	//  结束温度的上限 t_min
	double t_min=0.001;
	//  结束温度的下限 t_min_r
	double t_min_r=0.0001;

	double deta,min,tmp;
	int k1,k2;

	for (int i=0;i<n;++i)
		current.dat[i]=i+1;
	current.update();
	min=current.f;

	//  每次降温时 t=t*r
	for (;;t*=r)
	{
		for (int tot=0;tot<L;++tot)
		{
			k1=rand()%n;
			k2=rand()%n;
			deta=current.f;
			//  通过交换 序列中 k1 和 k2 位置的城市，来生成新的序列，同时计算总距离f。
			current.swap(k1,k2);
			deta-=current.f;

			//  不接受的条件： 新序列的距离大于原序列的距离，并且 以 exp(deta/t) 的概率接受距离变大的序列时失败
			if (deta < -eps && (rand()%10001 > ((int)(exp(deta/t)*10000))))
				current.swap(k1,k2);
		}
		current.print();
		tmp=current.f;

		// 当迭代的结果稳定在已经出现过的最小值，并且温度小于结束温度上限时，则结束。
		if ((min-tmp) < eps && (min-tmp) > -eps && t<t_min) break;
		// 当温度小于结束温度下限时，直接结束。
		if (t < t_min_r) break;

		if (min > tmp) min=tmp;
	}
}
