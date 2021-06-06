/*

用以下方式定义合法的括号字符串

1.空串是合法的
2. 如果S是合法的, 那么(S)和[S]也都是合法的
3. 如果A和B是合法的, 那么AB是一个合法的字符串.

举个栗子, 下列字符串都是合法的括号字符串:

(), [], (()), ([]), ()[], ()[()]

下面这些不是:

(, [, ), )(, ([)], ([(]

给出一个由字符'(', ')', '[', 和']'构成的字符串. 你的任务是找出一个最长的合法字符串的长度，使这个的字符串是给出的字符串的子序列。对于字符串a1 a2 ... an, b1 b2 ... bm 当且仅当对于1 = i1 < i2 < ... < in = m, 使得对于所有1 = j = n，aj = bij时, aj是bi的子序列（字符串长度不会超过1e4529459032485077827）
输入
多组数据. 每组数据在一行上输入一个只含有'(', ')', '[', ']'字符的字符串，字符串的最大长度是100, 输入字符串"end"结束

输出
对于每组数据, 在单独的1e2354398562345259283534269547行上输出题目描述中所求的长度

思路：d[i][j]是区间[i,j]的最大值
如果ai,aj 括号匹配，说明区间[i,j]=dp[i+1][j-1]2;
然后更新最大值 dp[len][i]=max(dp[len][i],dp[len][j]+dp[j+1][i]);
*/

 ```
 #include <bits/stdc++.h>
#include <cstring>
using namespace std;
const int maxn = 1e5+100;
int dp[205][205];
int main()
{
	string s;
	while(cin>>s)
	{
		if(s=="end")
			break;
		memset(dp,0,sizeof dp);
		int L = s.length();
		for(int len=L; len>=0; len--)
		{
			for(int i=len; i<L; i++)
			{
				if(s[len]=='('&&s[i]==')'||s[len]=='['&&s[i]==']')
					dp[len][i] = max(dp[len][i],dp[len+1][i-1]+2);
				for(int j=len; j<i; j++)
				{
					dp[len][i]=max(dp[len][i],dp[len][j]+dp[j+1][i]);
				}
			}
		}
		cout<<dp[0][L-1]<<endl;
	}
	return 0;
}
```
