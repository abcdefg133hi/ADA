#include <iostream>
#include <vector>


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    std::cin >> N;
    long long v[N+1][N+1];
    for(int i=1;i<N+1;i++)
    {
	for(int j=1;j<N+1;j++)
	{
	    long long temp;
	    std::cin >> temp;
	    v[i][j] = temp;
	}
    }


    std::vector<long long> result(N+1);
    long long now[N+2][N+2];
    long long pre[N+2][N+2];
    for(int i=1;i<N+1;i++)
    {
	for(int j=1;j<N+1;j++)
	{
	    pre[i][j] = 0;
	    now[i][j] = 0;
	}
	pre[i][N] = v[i][i];
	if(result[1]<v[i][i]) result[1] = v[i][i];
    }
    for(int s=1;s<=N;s++)
    {
	pre[s][N] = v[s][s];
	for(int k=1;k<=N;k++)
	{
	    for(int b=s+k-1;b<=N;b++)
	    {
		if(k==1 && b!=N)
		{
		    pre[s][b] = v[s][b+1];
		    continue;
		}
		if(k==1 && b==N) continue;
		long long temp(0);
		if(k%2==0) now[s][b] = 0;
		else pre[s][b] = 0;
		for(int alpha=s+k-2;alpha<b;alpha++)
		{
		    int idx;
		    if(b==N) idx = s;
		    else idx = b+1;
		    if(k%2==0) temp = pre[s][alpha] + v[alpha+1][idx];
		    else temp = now[s][alpha] + v[alpha+1][idx];
		    if(k%2==0 && now[s][b] < temp) now[s][b] = temp;
		    if(k%2==1 && pre[s][b] < temp) pre[s][b] = temp;
		}
		if(b==N && k%2==0 && now[s][b]>result[k]) result[k] = now[s][b];
		if(b==N && k%2==1 && pre[s][b]>result[k]) result[k] = pre[s][b];
	    }
	}
    }

    for(int k=1;k<=N;k++)
    {
	std::cout << result[k] << " ";
    }
    return 0;
}
