#include <iostream>
#include <vector>



std::vector<bool> if_use;
long long max(long long a, long long b, long long c)
{
    if(a>b)
    {
	if(a>c) return a;
    }

    if(b>c) return b;
    return c;
}
void DFS(std::vector<std::vector<int> > &graph, int begin, std::vector<int> &order, std::vector<int> &number)
{
    if_use[begin] = true;
    for(int i=0;i<graph[begin].size();i++)
    {
	if(!if_use[graph[begin][i]])
	{
	    DFS(graph, graph[begin][i], order, number);
	    number[begin] += number[graph[begin][i]];
	}
    }
    number[begin]+=1;
    order.push_back(begin);
}
int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int> > forest(N);
    std::vector<int> c;
    std::vector<int> D;
    if_use.resize(N);
    for(int i=0;i<N;i++)
    {
	int temp_f;
	std::cin >> temp_f;
	if(temp_f>=0)
	{
	    forest[temp_f].push_back(i);
	}
    }

    for(int i=0;i<N;i++)
    {
	int temp_c, temp_d;
	std::cin >> temp_c >> temp_d;
	c.push_back(temp_c);
	D.push_back(temp_d);
    }
    std::vector<int> order;
    std::vector<int> number(N);
    std::vector<int> c_tot(N);
    for(int i=0;i<N;i++)
    {
	if(!if_use[i]) DFS(forest, i, order, number);
    }

    std::vector<std::vector<long long> > d(M+1, std::vector<long long> (N+1, 0));
    for(int j=1;j<N+1;j++)
    {
	int now = order[j-1];
	for(int k=0;k<forest[now].size();k++)
	{
	    int doing = forest[now][k];
	    c_tot[now] += c_tot[doing];
	}
	c_tot[now] += c[now];
    }
    for(int i=0;i<=M;i++)
    {
	for(int j=1;j<N+1;j++)
	{
	    int now = order[j-1];
	    long long alpha = d[i][j-1];
	    long long beta;
	    if(i-c[now]>=0) beta = d[i-c[now]][j-1] + c[now];
	    else beta = -1;
	    long long gamma;
	    if(i-D[now]>=0) gamma = d[i-D[now]][j-number[now]] + c_tot[now];
	    else gamma = -1;
	    d[i][j] = max(alpha, beta, gamma);
	}
    }
    /*
    for(int i=0;i<c_tot.size();i++)
    {
	std::cout << order[i] << ": " << number[order[i]] << std::endl;
    }*/
    std::cout << d[M][N];
//    std::cout << max(4,6,10);
}
