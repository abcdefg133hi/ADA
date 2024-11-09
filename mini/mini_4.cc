#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph
{
public:
    int V;
    vector<vector<int> > graph;
    vector<bool> if_use;
    vector<vector<int> > graph_t;
    Graph(int v)
    {
	V = v;
	graph.resize(v);
	if_use.resize(v);
	graph_t.resize(v);
    }
    void init()
    {
	for(int i=0;i<if_use.size();i++)
	{
	    if_use[i] = false;
	}
    }
    void init_grapht()
    {
	for(int i=0;i<V;i++)
	{
	    for(int j=0;j<graph[i].size();j++)
	    {
		graph_t[graph[i][j]].push_back(i);
	    }
	}
    }
    void print_graph()
    {
	for(int i=0;i<V;i++)
	{
	    cout << i << ": ";
	    for(int j=0;j<graph[i].size();j++)
	    {
		cout << graph[i][j] << ", ";
	    }
	    cout << '\n';
	}
    }
    void print_graph_t()
    {
	for(int i=0;i<V;i++)
	{
	    cout << i << ": ";
	    for(int j=0;j<graph_t[i].size();j++)
	    {
		cout << graph_t[i][j] << ", ";
	    }
	    cout << '\n';
	}
    }
};
void DFS_1(Graph *work, int begin_v, vector<int> &order)
{
    work->if_use[begin_v] = true;
    for(int i=0;i<work->graph_t[begin_v].size();i++)
    {
	if(!work->if_use[work->graph_t[begin_v][i]])
	{
	    DFS_1(work, work->graph_t[begin_v][i], order);
	}
    }
    order.push_back(begin_v);
}

long long DFS_2(Graph *work, int begin_v)
{
    long long pre = 0;
    work->if_use[begin_v] = true;
    for(int i=0;i<work->graph[begin_v].size();i++)
    {
	if(!work->if_use[work->graph[begin_v][i]])
	{
	    pre += DFS_2(work, work->graph[begin_v][i]);
	}
    }
    return pre + 1;
}

long long SCC(Graph *work)
{
    vector<int> order;
    work->init_grapht();
    //first DFS for graph_t
    for(int i=0;i<work->V;i++)
    {
	if(!work->if_use[i]) DFS_1(work, i, order);
    }

    work->init();
    long long count = 0;
    //cout << "----------------\n";
    for(int i=work->V-1;i>=0;i--)
    {
	if(!work->if_use[order[i]])
	{
	    long long N;
	    N = DFS_2(work, order[i]);
	    //cout << N << ", " << i << endl;
	    count += (N*(N-1))/2;
	}
    }
    return count;
}


int main()
{
    int V;
    std::cin >> V;
    Graph *work = new Graph(V);
    int E;
    std::cin >> E;
    for(int i=0;i<E;i++)
    {
	int temp_1, temp_2;
	std::cin >> temp_1 >> temp_2;
	work->graph[temp_1-1].push_back(temp_2-1);
    }
    long long count = SCC(work);
    std::cout << count << endl;
//    work->print_graph();
 //   work->print_graph_t();
}
