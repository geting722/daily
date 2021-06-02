/*
HUEL_ACM队的队长给出了一个序列，想让学妹帮队长干活，作为学妹（或者想帮助某个漂亮的学妹）的你需要处理如下两种情况。

"C a b c"表示给[a, b]区间中的值全部增加c (-10000 ≤ c ≤ 10000)。

"Q a b" 询问[a, b]区间中所有值的和。

Input
第一行包含两个整数N, Q。1 ≤ N,Q ≤ 100000.

第二行包含n个整数，表示初始的序列A (-1000000000 ≤ Ai ≤ 1000000000)。

接下来Q行询问，格式如题目描述。

Output
对于每一个Q开头的询问，你需要输出相应的答案，每个答案一行。

Sample Input
10 5
1 2 3 4 5 6 7 8 9 10
Q 4 4
Q 1 10
Q 2 4
C 3 6 3
Q 2 4
Sample Output
4
55
9
15

区间查询，区间修改
我用的树状数组做的
树状数组，区间修改和区间查询的话需要利用差分维护两个数组
D[n]为差分数组
区间查询为
A[1]+A[2]+...+A[n]
= (D[1]) + (D[1]+D[2]) + ... + (D[1]+D[2]+...+D[n]) 
= n*D[1] + (n-1)*D[2] +... +D[n]
= n * (D[1]+D[2]+...+D[n]) - (0*D[1]+1*D[2]+...+(n-1)*D[n])
*/

```
#include <bits/stdc++.h>
const int maxn=5*1e5+100;
using namespace std;
typedef long long ll;
ll n,s1[maxn],s2[maxn];

ll lowbit(ll k)
{
	return k&-k;
}

void add(ll x,ll a)
{
	ll i=x;
	while(x<=n)
	{
		s1[x]+=a;
		s2[x]+=a*(i-1);
		x+=lowbit(x);
	}
}

ll sum(ll x)
{
	ll i=x;
	ll ans=0;
	while(x!=0)
	{
		ans+=i*s1[x]-s2[x];
		x-=lowbit(x);
	}
	return ans;
}

ll l,r;
int main()
{
	ll a,b=0;
	ll t;
	scanf("%lld%lld",&n,&t);
	for(ll i=1; i<=n; i++)
	{
		scanf("%lld",&a);
		add(i,a-b);
		b=a;
	}
	while(t--)
	{
		char temp;
		getchar();
		cin>>temp;
		if(temp=='C')
		{
			scanf("%lld%lld%lld",&l,&r,&a);
			add(l,a);
			add(r+1,-a);
		}
		else
		{
			ll c;
			scanf("%lld%lld",&b,&c);
			printf("%lld\n",sum(c)-sum(b-1));
		}
	}
}
```
