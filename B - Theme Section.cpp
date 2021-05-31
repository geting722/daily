/*
It's time for music! A lot of popular musicians are invited to join us in the music festival. Each of them will play one of their representative songs. To make the programs more interesting and challenging, the hosts are going to add some constraints to the rhythm of the songs, i.e., each song is required to have a 'theme section'. The theme section shall be played at the beginning, the middle, and the end of each song. More specifically, given a theme section E, the song will be in the format of ' EAEBE', where section A and section B could have arbitrary number of notes. Note that there are 26 types of notes, denoted by lower case letters 'a' - 'z'.

To get well prepared for the festival, the hosts want to know the maximum possible length of the theme section of each song. Can you help us?
Input
The integer N in the first line denotes the total number of songs in the festival. Each of the following N lines consists of one string, indicating the notes of the i-th (1 <= i <= N) song. The length of the string will not exceed 10^6.

Output
There will be N lines in the output, where the i-th line denotes the maximum possible length of the theme section of the i-th song.
 

Sample Input
6
xy
abc
aaa
aaaaba
aaxoaaaaa
aaaaabaaa
Sample Output
0
0
1
1
2
2

思路：next1数组存的是前后缀相同的长度,中间不可重叠。
开始想的是在next1[len]---len-next1[len]这段区间找个最大值然后与最小值比较
*/
```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+100;
int next1[maxn];
int n;
string a;
void get_next()
{
	int i=0,k=-1;
	int len = a.length();
	next1[0]=-1;
	while(i<len)
	{
		if(k==-1||a[k]==a[i])
		{
			next1[++i]=++k;
		}
		else k=next1[k];
	}
}
int main()
{
	cin>>n;
	while(n--)
	{
		memset(next1,-1,sizeof next1);
		cin>>a;
		get_next();
		int j=a.length();
		int ans=0;
//		for(int i=0; i<=a.length(); i++)
//			cout<<next1[i]<<" ";
//		cout<<endl;
		int maxa=0;
		for(int i=next1[j]; i; i=next1[i])
		{
			for(int k=i+i; k<=j-i; k++)
			{
				if(next1[k]>=i)
				{
					maxa = max(maxa, i);
				}
			}
		}
		cout<<(maxa<next1[j]?maxa:next1[j])<<endl;

	}
	return 0;
}
*/
