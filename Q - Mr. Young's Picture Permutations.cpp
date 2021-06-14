/*
有N个学生合影，站成左对齐的k排，每行分别有N1,N2…NK个人，第一排站最后，第k排站之前。
学生身高依次是1…N。在合影时候要求每一排从左到右递减，每一列从后面到前也递减，一共有多少总方案
Input
输入
每组测试数据包含两行。第一行给出行数k
第二行包含从后到前（n1，n2，…，nk）的行的长度，作为由单个空格分隔的十进制整数。
问题数据以0结束。
N<=30, k<=5;
Output
输出
输出每组数据的方案数
Sample Input
1
30
5
1 1 1 1 1
3
3 2 1
4
5 3 3 1
5
6 5 4 3 2
2
15 15
0
Sample Output
1
1
16
4158
141892608
9694845
题解：dp[a][b][c][d][e]表示这5行的状态 考虑一下如果第一排放满了人第二排最多也是15个人因为列要递增
所以可以优化下空间
用的是顺转移，直接枚举
*/
```
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
using namespace std;
ll len[31],dp[31][16][11][8][7];
int main()
{
	ll k,n;
	while(cin>>k)
	{
		if(k==0)
			break;
		memset(len,0,sizeof len);
		memset(dp,0,sizeof dp);
		dp[0][0][0][0][0]=1;
		for(int i=1; i<=k; i++)
			cin>>len[i];
		for(int e=0; e<=len[5]; e++)
			for(int d=e; d<=len[4]; d++)
				for(int c=d; c<=len[3]; c++)
					for(int b=c; b<=len[2]; b++)
						for(int a=b; a<=len[1]; a++)
						{
							dp[a+1][b][c][d][e]+=dp[a][b][c][d][e];
							dp[a][b+1][c][d][e]+=dp[a][b][c][d][e];
							dp[a][b][c+1][d][e]+=dp[a][b][c][d][e];
							dp[a][b][c][d+1][e]+=dp[a][b][c][d][e];
							dp[a][b][c][d][e+1]+=dp[a][b][c][d][e];
						}
		printf("%lld\n",dp[len[1]][len[2]][len[3]][len[4]][len[5]]);
	}
	return 0;
}
```
