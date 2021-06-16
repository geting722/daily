/*
你工作以后, KPI 就是你的全部了. 我开发了一个服务，取得了很大的知名度。数十亿的请求被推到一个大管道后同时服务从管头拉取请求。让我们来定义每个请求都有一个重要值。我的KPI是由当前管道内请求的重要值的中间值来计算。现在给你服务记录，有时我想知道当前管道内请求的重要值得中间值。
Input
有大约100组数据。

每组数据第一行有一个n(1≤n≤10000)，代表服务记录数。

接下来有n行，每一行有3种形式
  "in x": 代表重要值为x(0≤x≤109)的请求被推进管道。
  "out": 代表服务拉取了管道头部的请求。
  "query: 代表我想知道当前管道内请求重要值的中间值. 那就是说，如果当前管道内有m条请求, 我想知道，升序排序后第floor(m/2)+1th 条请求的重要值.

为了让题目简单，所有的x都不同，并且如果管道内没有值，就不会有"out"和"query"操作。
Output
对于每组数据，先输出一行

Case #i:
然后每一次"query"，输出当前管道内重要值的中间值。
Sample Input
6
in 874
query
out
in 24622
in 12194
query
Sample Output
Case #1:
874
24622

题解：用set维护kpi
用两个set分别维护分别维护[1,m/2+1],[m/2+1+1,n]
*/
```
#include <bits/stdc++.h>
#include <queue>
#include <set>
#include <string>
using namespace std;
queue<int> que;
set<int> a,b;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	int ans = 1;
	while(cin>>n)
	{

		int m=0,x;
		while(!que.empty())
			que.pop();
		a.clear();
		b.clear();
		string s;
		cout<<"Case #"<<ans++<<":"<<endl;
		for(int k=0; k<n; k++)
		{
			string s;
			cin>>s;
			if(s[0]=='i')
			{
				cin>>x;
				que.push(x);
				if(a.empty()||x<*a.rbegin())
					a.insert(x);
				else
					b.insert(x);
				m++;
			}
			else if(s[0]=='o')
			{
				int t=que.front();
				que.pop();
				if(a.find(t)==a.end())
					b.erase(t);
				else
					a.erase(t);
				m--;
			}
			else if(s[0]=='q')
			{
//				printf("Case #%d:\n",ans++);
				cout<<*a.rbegin()<<endl;
			}
			while(m>0&&a.size()>m/2+1)
			{
				int tem=*a.rbegin();
				a.erase(tem);
				b.insert(tem);
			}
			while(m>0&&a.size()<m/2+1)
			{
				int tem=*b.begin();
				b.erase(tem);
				a.insert(tem);
			}
		}
	}
	return 0;
}
```
