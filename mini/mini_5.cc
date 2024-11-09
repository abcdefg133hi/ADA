#include <iostream>
#include <vector>
#include <queue>

typedef std::pair<long long, int> pp;

//std::vector<std::vector<long long> > graph;
std::vector<std::vector<pp> > graph_list;
std::priority_queue<pp, std::vector<pp>, std::greater<pp> > Q;
std::vector<bool> if_use;

long long prims()
{
    int now = 0;
    long long result(0);
    if_use[now] = true;
    for(int i=0;i<graph_list[now].size();i++)
    {
	int doing = graph_list[now][i].second;
	Q.push(std::make_pair(graph_list[now][i].first, doing));
    }
//    std::cout << "rrr; " << result << std::endl;
    while(!Q.empty())
    {
	now = Q.top().second;
	long long weight = Q.top().first;
	Q.pop();
	if(if_use[now]) continue;
	if_use[now] = true;
	result += weight;
//	std::cout << "rrr; " << result << std::endl;
	for(int i=0;i<graph_list[now].size();i++)
	{
	    int doing = graph_list[now][i].second;
	    Q.push(std::make_pair(graph_list[now][i].first, doing));
	}
    }
    return result;
}

int main()
{
    int N, M;
    std::cin >> N >> M;
    graph_list.resize(N);
    if_use.resize(N);
    //graph.resize(N, std::vector<long long>(N));
    for(int i=0;i<M;i++)
    {
	int temp_1;
	int temp_2;
	long long temp_w;
	std::cin >> temp_1 >> temp_2 >> temp_w;
//	graph[temp_1-1][temp_2-1] = temp_w;
//	graph[temp_2-1][temp_1-1] = temp_w;
	graph_list[temp_1-1].push_back(std::make_pair(temp_w,temp_2-1));
	graph_list[temp_2-1].push_back(std::make_pair(temp_w,temp_1-1));
    }
    std::cout << prims();
}
