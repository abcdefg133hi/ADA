#include <iostream>
#include <queue>
#include <vector>

std::vector<std::vector<long long> > graph;
std::vector<std::vector<long long> > graph_list;

typedef std::pair<long long, int> pp;

/*long long min(long long a, long long b, bool &judge)
{
    judge = false;
    if(a<b) return a;
    judge = true;
    return b;
}*/

long long min_(std::vector<long long> target)
{
    int size = target.size();
    long long min = target[0];
    for(int i=1;i<size;i++)
    {
	if(target[i]<min)
	{
	    min = target[i];
	}
    }
    return min;
}

std::vector<long long> min_dist(int begin, int end, int N)
{
    std::vector<long long> d(N);
    std::priority_queue<pp, std::vector<pp>, std::greater<pp> > Q;
    for(int i=0;i<N;i++)
    {
	if(i==0 || i==begin) d[i] = 0;
	else d[i] = 1E9;
	Q.push(std::make_pair(d[i],i));
    }
    while(!Q.empty())
    {
	int now = Q.top().second;
	//std::cout << d[2] << std::endl;
	Q.pop();
	//for(int i=0;i<N;i++)
	//{
	    for(int i=0;i<graph_list[now].size();i++)
	    {
		long long idx = graph_list[now][i];
//		int temp = graph[now][idx];
		if(graph[now][idx]+d[now]<d[idx])
		{
		   d[idx] = graph[now][idx] + d[now];
		   Q.push(std::make_pair(d[idx], idx));
		}
	    }
	    //if(graph[now][i]==-1) continue;
	//}
    }
    return d;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int M, N;
    std::cin >> N >> M;
    graph.resize(N, std::vector<long long>(N));
    graph_list.resize(N);
    for(int i=0;i<N;i++)
    {
	for(int j=0;j<N;j++)
	{
	    graph[i][j] = -1;
	}
    }
    for(int i=0;i<M;i++)
    {
	int temp_1, temp_2;
	long long temp_m;
	std::cin >> temp_1 >> temp_2 >> temp_m;
	graph[temp_1-1][temp_2-1] = temp_m;
	graph_list[temp_1-1].push_back(temp_2-1);
    }
    //std::exit(0);
    std::vector<long long> all;
    std::vector<long long> hi;
    for(int i=1;i<N;i++)
    {
	long long temp = graph[0][i];
	graph[0][i] = 0;
	long long alpha = 0;
	hi = min_dist(i,0,N);
	for(int j=1;j<N;j++)
	{
	    alpha += hi[j];
	}
	all.push_back(alpha);
	graph[0][i] = temp;
    }
    long long result = min_(all);
    std::cout << result;
}
