/*
奶牛们最近的旅游计划，是到苏必利尔湖畔，享受那里的湖光山色，以及明媚的阳光。作为整个旅游的策划者和负责人，贝茜选择在湖边的一家著名的旅馆住宿。这个巨大的旅馆一共有N 间客房，它们在同一层楼中顺次一字排开，在任何一个房间里，只需要拉开窗帘，就能见到波光粼粼的湖面。

贝茜一行，以及其他慕名而来的旅游者，都是一批批地来到旅馆的服务台，希望能订到D_i (1 <= D_i <= N)间连续的房间。服务台的接待工作也很简单：如果存在r满足编号为r..r+D_i-1的房间均空着，他就将这一批顾客安排到这些房间入住；如果没有满足条件的r，他会道歉说没有足够的空房间，请顾客们另找一家宾馆。如果有多个满足条件的r，服务员会选择其中最小的一个。

旅馆中的退房服务也是批量进行的。每一个退房请求由2个数字X_i、D_i描述，表示编号为X_i..X_i+D_i-1 (1 <= X_i <= N-D_i+1)房间中的客人全部离开。退房前，请求退掉的房间中的一些，甚至是所有，可能本来就无人入住。

而你的工作，就是写一个程序，帮服务员为旅客安排房间。你的程序一共需要处理M 个按输入次序到来的住店或退房的请求。第一个请求到来前，旅店中所有房间都是空闲的。

输入格式
第一行输入n，m ，n代表有n个房间，编号为1---n，开始都为空房，m表示以下有m行操作，以下 每行先输入一个数 i ，表示一种操作：

若i为1，表示查询房间，再输入一个数x，表示在1--n 房间中找到长度为x的连续空房，输出连续x个房间中左端的房间号，尽量让这个房间号最小，然后入住。若找不到长度为x的连续空房，输出0。

若i为2，表示退房，再输入两个数 x，y 代表 房间号 x---x+y-1 退房，即让房间为空。

输出格式
对于每一个入住请求，输出查询出可以入住的最小房间号，如果不能安排入住输出0；

样例输入
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6
样例输出
1
4
7
0
5
数据范围
1 <= N <= 50,000； 1 <= M < 50,000


题解:线段树维护三个值，1表示能住，0表示已经有人住了，区间的连续前缀和和连续后缀和，区间的最大值


*/
```
#include <iostream>
#include <algorithm>
using namespace std;
const int N=500000+1000;
struct node
{
	int l,r;
	int sum;
	int start;
	int end;
	int add;
} tr[N<<2];
int n;
int m;
void build(int u,int l,int r)
{
	tr[u]= {l,r,r-l+1,r-l+1,r-l+1,0};
	if(l==r)return ;
	int mid=(l+r)>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	return ;
}

void pushdown(int u)
{
	if(tr[u].l==tr[u].r)return ;
	if(tr[u].add==1)
	{
		tr[u<<1]= {tr[u<<1].l,tr[u<<1].r,0,0,0,1};
		tr[u<<1|1]= {tr[u<<1|1].l,tr[u<<1|1].r,0,0,0,1};
		tr[u].add=0;
	}
	if(tr[u].add==2)
	{
		tr[u<<1]= {tr[u<<1].l,tr[u<<1].r,tr[u<<1].r-tr[u<<1].l+1,tr[u<<1].r-tr[u<<1].l+1,tr[u<<1].r-tr[u<<1].l+1,2};
		tr[u<<1|1]= {tr[u<<1|1].l,tr[u<<1|1].r,tr[u<<1|1].r-tr[u<<1|1].l+1,tr[u<<1|1].r-tr[u<<1|1].l+1,tr[u<<1|1].r-tr[u<<1|1].l+1,2};
		tr[u].add=0;
	}
}
int query(int u,int x)
{
	pushdown(u);
	if(tr[u<<1].sum>=x)
	{
		return query(u<<1,x);
	}
	else if(tr[u<<1].end+tr[u<<1|1].start>=x)
	{
		return tr[u<<1|1].l-tr[u<<1].end;
	}
	return query(u<<1|1,x);
}
void pushup(int u)
{
	tr[u].sum=max(max(tr[u<<1].sum,tr[u<<1|1].sum),tr[u<<1].end+tr[u<<1|1].start);

	if(tr[u<<1].sum==tr[u<<1].r-tr[u<<1].l+1)
	{
		tr[u].start=tr[u<<1].r-tr[u<<1].l+1+tr[u<<1|1].start;
	}
	else tr[u].start=tr[u<<1].start;

	if(tr[u<<1|1].sum==tr[u<<1|1].r-tr[u<<1|1].l+1)
	{
		tr[u].end=tr[u<<1].end+tr[u<<1|1].r-tr[u<<1|1].l+1;
	}
	else tr[u].end=tr[u<<1|1].end;
}
void modify(int u,int l,int r)
{
	pushdown(u);
	if(l<=tr[u].l&&tr[u].r<=r)
	{
		tr[u]= {tr[u].l,tr[u].r,0,0,0,1};
		return ;
	}
	int mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid)
	{
		modify(u<<1,l,r);
	}
	if(r>mid)
	{
		modify(u<<1|1,l,r);
	}
	pushup(u);
}
void modify1(int u,int l,int r)
{
	pushdown(u);
	if(l<=tr[u].l&&tr[u].r<=r)
	{
		tr[u]= {tr[u].l,tr[u].r,tr[u].r-tr[u].l+1,tr[u].r-tr[u].l+1,tr[u].r-tr[u].l+1,2};
		return ;
	}
	int mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid)
	{
		modify1(u<<1,l,r);
	}
	if(r>mid)
	{
		modify1(u<<1|1,l,r);
	}
	pushup(u);
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	build(1,1,n);
	while(m--)
	{
//		cout<<"uuu";
//		cout<<tr[1].sum<<endl;
		int f;
		cin>>f;
		if(f==1)
		{
			int x;
			cin>>x;
			if(tr[1].sum>=x)
			{
				int t=query(1,x);
				cout<<t<<endl;
				modify(1,t,t+x-1);
			}
			else
			{
				cout<<0<<endl;
			}

		}
		else
		{
			int x,y;
			cin>>x>>y;
			modify1(1,x,x+y-1);
		}
	}
	return 0;
}
```
