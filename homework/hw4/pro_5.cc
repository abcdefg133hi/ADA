#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
long long d[400+2][400+2][400+2];
long long v[401][401];
long long result[401];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(NULL));
    int N;
    cin >> N;
    vector<int> random;
    for(int i=0;i<N;i++) random.push_back(i+1);
    random_shuffle(random.begin(), random.end());
    for(int i=1;i<N+1;i++)
    {
	for(int j=1;j<N+1;j++)
	{
	    cin >> v[i][j];
	}
    }


    // k: cut, s: start, b: end.

	for(int k=1;k<=N;k++)
	{
	    int use = min(N-k+1,2400/k); //use: pick the number of start that we would use.
	    for(int q=0;q<use;q++)
	    {
		int s = random[q];
		for(int b=1;b<=N;b++)
		{
		    int idx=b==N?1:b+1; //N+1=1
		    if(k==1) // Initialization
		    {
			d[s][k][b] = v[s][idx];
			continue;
		    }
		    if(b>=s)
		    {
			for(int alpha=b-1;alpha>=s+k-2;alpha--) //alpha: median
			{
			    int next=alpha==N?1:alpha+1; //next=alpha+1, N+1=1.
			    if(d[s][k][b] < d[s][k-1][alpha] + v[next][idx]) d[s][k][b] = d[s][k-1][alpha] + v[next][idx];
			}
		    }
		    else
		    {
			int ooo=N+b;   // if b<s, then we need to consider from s, s+1,... back to b.
			for(int beta=ooo-1;beta>=s+k-2;beta--)
			{
			    int alpha=beta>N?beta-N:beta;
			    int next=alpha==N?1:alpha+1;
			    if(d[s][k][b] < d[s][k-1][alpha] + v[next][idx]) d[s][k][b] = d[s][k-1][alpha] + v[next][idx];
			}
		    }
		}
	    }
	}


    //Comparison
    for(int k=1;k<=N;k++)
    {
	result[k] = d[1][k][N];
	for(int s=2;s<=N;s++)
	{
	    if(result[k]<d[s][k][s-1]) result[k] = d[s][k][s-1];
	}
	cout << result[k] << " ";
    }
    return 0;
}
