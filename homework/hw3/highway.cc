#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

typedef std::pair<int, int> pp;
struct object
{
    long long l;
    long long c;
    int idx;
};

std::vector<std::vector<object> > graph;
std::vector<int> length;
std::vector<int> cost;


struct cmp
{
    bool operator()(std::pair<int,object> a, std::pair<int,object> b)
    {
	if(a.second.l < b.second.l) return false;
	if(a.second.l == b.second.l)
	{
	    if(a.second.c < b.second.c) return false;
	}
	return true;
    }
};
long long prims(int N)
{
    std::vector<long long> cost(N);
    std::vector<long long> length(N);
    std::vector<bool> if_use(N);
    std::priority_queue<std::pair<int,object> , std::vector<std::pair<int, object> >, cmp> Q;
    int now = 0;
    if_use[now] = true;
    for(int i=0;i<graph[now].size();i++)
    {
	Q.push(std::make_pair(now, graph[now][i]));
    }
    long long result = 0;
    long long pre_result = 0;
    while(!Q.empty())
    {
	int hello = Q.top().second.idx;
	int safe = Q.top().first;
	long long temp = Q.top().second.l;
	long long hey = Q.top().second.c;
	Q.pop();
	if(if_use[hello]) continue;
	if_use[hello] = true;
	bool if_equal;
	if(length[now]<temp)
	{
	    pre_result = hey;
	    length[hello] = temp;
	}
	else if(length[now]==temp)
	{
	    pre_result = hey;
	    length[hello] = length[now];
	}
	else
	{
	    pre_result = cost[now];
	    length[hello] = length[now];
	}
	cost[hello] = pre_result;
	result += pre_result;
	now = hello;
	for(int i=0;i<graph[now].size();i++)
	{
	    int doing = graph[now][i].idx;
	    if(if_use[doing]) continue;
	    if(graph[now][i].l==length[now]) graph[now][i].c += cost[now];
	    Q.push(std::make_pair(now, graph[now][i]));
	}
    }
    return result;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    graph.resize(n);
    for(int i=0;i<m;i++)
    {
	int temp_u, temp_v, temp_l, temp_c;
	std::cin >> temp_u >> temp_v >> temp_l >> temp_c;
	object temp;
	temp.l = temp_l;
	temp.c = temp_c;
	temp.idx = temp_v;
	graph[temp_u].push_back(temp);
	temp.idx = temp_u;
	graph[temp_v].push_back(temp);
    }
    std::cout << prims(n);
}
