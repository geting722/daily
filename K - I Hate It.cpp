/*

很多学校流行一种比较的习惯。茜茜学姐很喜欢询问，从某某到某某当中，分数最高的是多少。
这让很多漂亮的学妹很喜欢。

不管你喜不喜欢，现在需要你做的是，就是按照茜茜学姐的要求，写一个程序，模拟茜茜学姐的询问。当然，茜茜学姐有时候需要更新某位同学的成绩。
Input
本题目包含多组测试，请处理到文件结束。
在每个测试的第一行，有两个正整数 N 和 M ( 0<N<=200000,0<M<5000 )，分别代表学生的数目和操作的数目。
学生ID编号分别从1编到N。
第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。
接下来有M行。每一行有一个字符 C (只取'Q'或'U') ，和两个正整数A，B。
当C为'Q'的时候，表示这是一条询问操作，它询问ID从A到B(包括A,B)的学生当中，成绩最高的是多少。
当C为'U'的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。
Output
对于每一次询问操作，在一行里面输出最高成绩。
Sample Input
5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5
Sample Output
5
6
5
9


  
Hint
Huge input,the C function scanf() will work better than cin
 
线段树模板，维护区间最大值，数组开小了一直报时间超限
 
*/
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2*1e5+5;
int sum[maxn<<2],lazy[maxn<<2];
int s[maxn<<2];
inline ll ls(ll x)//左子节点
{
	return x<<1;
}

inline ll rs(ll x)//右子节点
{
	return x<<1|1;
}

void pushup(int k)
{
	sum[k]=max(sum[ls(k)],sum[rs(k)]);
}

void push_down(int k,int m)
{
	if(lazy[k])
	{
		lazy[ls(k)]=lazy[k];
		lazy[rs(k)]=lazy[k];
		sum[ls(k)]=lazy[k]*(m-(m>>1));
		sum[rs(k)]=lazy[k]*(m>>1);
		lazy[k]=0;
	}
}

void build(int l,int r,int k)
{
	if(l==r)
	{
		sum[k]=s[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,ls(k));
	build(mid+1,r,rs(k));
	pushup(k);
}

void update(int L,int c,int l,int r,int k)
{
	if(l==r)
	{
		sum[k]=c;
//		lazy[k]=c;
		return;
	}
	//push_down(k,r-l+1);
	int mid=(l+r)>>1;
	if(L<=mid)
		update(L,c,l,mid,ls(k));
	else
		update(L,c,mid+1,r,rs(k));
	pushup(k);
}

int query(int L,int R,int l,int r,int k)
{
	if(L<=l&&R>=r)
		return sum[k];
	int mid=(l+r)>>1;
	int ret=0;
	if(L<=mid)
		ret=max(ret,query(L,R,l,mid,k*2));
	if(R>mid)
		ret=max(ret,query(L,R,mid+1,r,k*2+1));
	return ret;
}

int main()
{
	int n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		for(int i=1; i<=n; i++)
		{
			scanf("%d",s+i);
		}
		build(1,n,1);
		getchar();
		while(m--)
		{
			char ch;
			int b,c;
			scanf("%c%d%d",&ch,&b,&c);
			if(ch=='U')
				update(b,c,1,n,1);
			else printf("%d\n",query(b,c,1,n,1));
			
		}

	}

	return 0;
}

```
