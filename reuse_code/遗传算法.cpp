//  旅行商问题   
//
//  遗传算法
//
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

/*
 *    个体编码方案：每个城市有一个权值，旅行的路径是按城市的权值从小到大依次旅行（权值相同时，先去编号小的城市）。
 *    结构体Seqce用于保存一个解，数组w存储每个城市的权值，实数f表示旅行的路径距离。
 */

int GROUP_SIZE; // 种群规模
const int GEN_MAX=1000;     // 最大遗传代数
const double PS=0.6;	  // 保留概率
const double PV=0.05;	  // 变异概率

struct City
{
	double x,y;
	char name[20];
}citys[50];
struct Seqce
{
	int w[30];
	double f;
	void calc();
};

int n,m;
double Dis[35][35];
Seqce group[100011], bestn;

int _a[35],_b[60];
long long tot;
void sort_by_weight(int* a_w);
void rand_sequence(int*);
void breed(Seqce& u, Seqce& v);
void variation();
void tsp_work();
int main(int argc, char** argv)
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);

	srand(std::time(NULL));
	scanf("%d",&n);
	//   m为城市的权值范围
	m=n<<1;
	//   根据n的范围初始化种群
	if (n <= 20) 
		GROUP_SIZE=1000;
	else
		GROUP_SIZE=100000;

	for (int i=1;i<=n;++i)		
		scanf("%s%lf%lf",citys[i].name,&citys[i].x,&citys[i].y);

	//  预先计算出任意两个城市间的距离
	for (int i=1;i<=n;++i)
		for (int j=1;j<=i;++j)
			Dis[i][j]=Dis[j][i]=sqrt((citys[i].x-citys[j].x)*(citys[i].x-citys[j].x)+(citys[i].y-citys[j].y)*(citys[i].y-citys[j].y));
	tsp_work();
	
	sort_by_weight(bestn.w);
	for (int i=1;i<=n;++i)
		printf("%s ",citys[_a[i]].name);
	printf("%.5lf\n",bestn.f);
	return 0;
}

void Seqce::calc()
{
	sort_by_weight(w);
	f=Dis[_a[1]][_a[n]];
	for (int i=2;i<=n;++i)
		f+=Dis[_a[i-1]][_a[i]];
}

//   将城市按照数组a_w中的权值大小排序，结果保存到全局的_a数组中。
void sort_by_weight(int* a_w)
{
	memset(_b,0,sizeof(_b));
	for (int i=1;i<=n;++i)
		++_b[a_w[i]];
	for (int i=1;i<m;++i)
		_b[i]+=_b[i-1];
	for (int i=n;i>=1;--i)
		_a[_b[a_w[i]]--]=i;
}

bool GroupCmp(const Seqce& u, const Seqce& v)
{
	return (u.f < v.f);
}
void tsp_work()
{
	for (int i=0;i<GROUP_SIZE;++i)
	{
		for (int j=1;j<=n;++j)
			group[i].w[j]=rand()%m;
		group[i].calc();
	}

	int nn=GROUP_SIZE*PS;   //  当前规模的种群中的样本的保留个数
	int nv=GROUP_SIZE*n*PV; //  当前规模的种群中的变异染色体个数
	bestn=group[0];

	int time_limit=4*60*1000+30*1000;  // 4分30秒的毫秒数

	//   算法结束条件，遗传代数达到上限(GEN_MAX)
	for (int gp=0;gp<GEN_MAX;++gp)
	{
		//   计算当前种群中每个样本的适应值（就是旅行的距离）
		for (int i=0;i<GROUP_SIZE;++i)
			group[i].calc();

		//   将所有解排序，并更新全局的最优解
		std::sort(group, &group[GROUP_SIZE], GroupCmp);
		if (group[0].f < bestn.f)
			bestn=group[0];

		//   仅保留种群中较优的nn个解
		for (int i=nn;i<GROUP_SIZE;++i)
			group[i]=group[i-nn];
		//   二叉繁殖产生两个新解
		for (int i=0;i+i<GROUP_SIZE;++i)
			breed(group[i], group[GROUP_SIZE-i-1]);
		//   发生变异 : 随机的某个样本中的某个城市的权值发生改变。
		for (int i=0;i<nv;++i)
			group[rand()%GROUP_SIZE].w[rand()%n+1]=rand()%m;

		//   用时超过4分30秒时，不再继续求解。
		tot=clock();
		if (tot > time_limit) break;
	}
}

//  二叉繁殖： 交换两个解的尾部（长为len的段，len随机）
void breed(Seqce& u, Seqce& v)
{
	int len=rand()%n;
	int tt;
	for (int i=1;i<=len;++i)
	{
		tt=u.w[i];
		u.w[i]=v.w[i];
		v.w[i]=tt;
	}
}
