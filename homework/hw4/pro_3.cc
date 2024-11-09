#include "ypglpk.hpp"
#include <iostream>
//#include <vector>

struct object
{
    int vertex;
    long weight;
    int index;
};
typedef std::pair<int, long long> pp;
//std::vector<std::vector<pp> > graph; //pair:(adjacent, weight)
std::vector<std::vector<object> > graph;
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    //ypglpk::set_output(false);
    int N, M;
    std::cin >> N >> M;
    graph.resize(N);
    std::vector<double> x(M);
    std::vector<double> w;

    for(int i=0;i<M;i++)
    {
	int temp_1, temp_2;
	long temp_w;
	std::cin >> temp_1 >> temp_2 >> temp_w;
	//graph[temp_1].push_back(std::make_pair(temp_2, temp_w));
	object temp;
	temp.vertex = temp_2-1;
	temp.weight = temp_w;
	temp.index = i;
	/*
	if(temp_1==N)
	{
	    temp.weight = -1;
	    temp_w = -1;
	}*/
	graph[temp_1-1].push_back(temp);
	w.push_back(temp_w);
    }
    for(int i=0;i<N;i++) w.push_back(0);
    std::vector<std::vector<double> > A(2*N+2+M+N, std::vector<double>(M+N));
    std::vector<double> b(2*N+2+M+N);
    for(int i=0;i<N;i++)
    {
	if(i==0) b[i] = 1;
	else b[i] = 0;
	b[i+N] = 1;
	for(int j=0;j<graph[i].size();j++)
	{
	    int idx = graph[i][j].index;
	    int ver = graph[i][j].vertex;
	    A[i][idx] = 1;
	    A[ver][idx] = -1;
	    A[2*N+2+idx][M+i] = 1;
	    A[2*N+2+idx][idx] = N;
	    A[2*N+2+idx][M+ver] = -1;
	    if(i==ver) A[2*N+2+idx][M+ver] = 0;
	    b[2*N+2+idx] = N-1;
//	    std::cout << N+ver << "  ";
	    A[N+ver][idx] = 1;
	    if(i==0)
	    {
		//std::cout << "dd" << std::endl;
		//int idx = graph[i][j].index;
		A[2*N][idx] = -1;
	    }
	    if(i==N-1)
	    {
		A[i][idx] = 100;
		A[ver][idx] = -1;
	    }
	    if(ver==N-1)
	    {
//		std::cout << idx  << std::endl;
		//int idx = graph[i][j].index;
		A[2*N+1][idx] = -1;
	    }
	}
    }
    for(int i=0;i<N;i++)
    {
	A[2*N+2+M+i][M+i] = -1;
	b[2*N+2+M+i] = -30;
    }
    //std::cout << A[2*N][0];
    b[2*N] = -1;
    b[2*N+1] = -1;
    std::pair<double, std::vector<double> > res;
    //res = ypglpk::linear_programming(A, b, w);

    std::vector<int> vartype(M+N);
    for(int i=0;i<M;i++)
    {
	vartype[i] = GLP_BV;
    }
    for(int i=M;i<M+N;i++)
    {
	vartype[i] = GLP_CV;
    }

    res = ypglpk::mixed_integer_linear_programming(A, b, w, vartype);
    if(res.second.empty()){
    	 std::cout << -1;
    }
    else{
	std::cout << (int)res.first << "\n";
	for(int i=0;i<M;i++)
	{
	    std::cout << res.second[i];
	}
    }

}
