#include <iostream>

using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    int K;
    long long M;
    cin >> N >> K >> M;
    long long pre[K+1][K+1];
    long long curr[K+1][K+1];

    for(int i=0;i<=N;i++)
    {
	for(int j=0;j<=K;j++)
	{
	    for(int p=0;p<=K;p++)
	    {
		if(i==0)
		{
		    if(M==1) pre[j][p] = 0;
		    else pre[j][p] = 1;
		}
		else if (j==0 && p==0)
		{
		    if(M==1) curr[j][p] = 0;
		    else curr[j][p] = 1;
		}
		else if(j==0 || p==K)
		{
		    curr[j][p] = curr[j][p-1]+pre[j][p] >= M ? curr[j][p-1]+pre[j][p]-M : curr[j][p-1]+pre[j][p];
		}
		else if(p==0)
		{
		   curr[j][p] = curr[j-1][p+1]+pre[j][p] >= M ?curr[j-1][p+1]+pre[j][p]-M:curr[j-1][p+1]+pre[j][p];
		   curr[j][p] = curr[j][p]-pre[j-1][p] < 0 ?curr[j][p]-pre[j-1][p]+M:curr[j][p]-pre[j-1][p];
		}
		else
		{
		    curr[j][p] = curr[j-1][p+1]+curr[j][p-1]>= M ? curr[j-1][p+1]+curr[j][p-1]-M : curr[j-1][p+1]+curr[j][p-1];
		    curr[j][p] = curr[j][p]+pre[j][p]>= M ? curr[j][p]+pre[j][p]-M : curr[j][p]+pre[j][p];
		    curr[j][p] = curr[j][p]-curr[j-1][p] < 0 ? curr[j][p] - curr[j-1][p] + M : curr[j][p] - curr[j-1][p];
		    curr[j][p] = curr[j][p] - pre[j-1][p] < 0 ? curr[j][p] - pre[j-1][p]+M : curr[j][p] - pre[j-1][p];
		}
	    }
	}
	if(i>0 && i<N)
	{
	    for(int j=0;j<=K;j++)
	    {
		for(int p=0;p<=K;p++)
		{
		    pre[j][p] = curr[j][p];
		}
	    }
	}
    }
    if(M==1) cout << 0;
    else cout << curr[K][0];

}
