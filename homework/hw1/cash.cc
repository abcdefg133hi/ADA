#include <iostream>
#include <vector>
#include <time.h>


int maxValue(std::vector<int> array)
{
    const int N = array.size();
    if(N==0) return 0;
    int max = array[0];
    for(int i=1;i<N;i++)
    {
	if(array[i]>max) max = array[i];
    }
    return max;
}

void sort(int *gem, int N)
{
    if(N==1) return;
    int left[(N+1)/2], right[N/2];
    for(int i=0;i<N/2;i++)
    {
	left[i] = gem[i];
	right[i] = gem[(N+1)/2+i];
    }
    if(N%2==1) left[(N+1)/2-1] = gem[(N+1)/2-1];

    sort(left, (N+1)/2);
    sort(right, N/2);

    int left_idx(0), right_idx(0), total_idx(0);
    while(total_idx<N)
    {
	if(left_idx>=(N+1)/2)
	{
	    for(int i=right_idx;i<N/2;i++)
	    {
		gem[(N+1)/2+i] = right[i];
	    }
	    break;
	}

	if(right_idx>=N/2)
	{
	    for(int i=left_idx;i<(N+1)/2;i++)
	    {
		gem[N/2+i] = left[i];
	    }
	    break;
	}

	if(left[left_idx]>right[right_idx])
	{
	    gem[total_idx] = left[left_idx];
	    left_idx++;
	}
	else
	{
	    gem[total_idx] = right[right_idx];
	    right_idx++;
	}
	total_idx++;
    }
}

int normalWay(int tot_money, int *gem, int size)
{
    int money = tot_money;

    for(int i=0;i<size;i++)
    {
	if(money==0 || money<gem[i]) continue;
	money = money % gem[i];
    }
    return tot_money - money;
}

int smartWay(int tot_money, int *gem, int N, int *store, const int NN)
{

    if(N==1) return (tot_money/gem[0])*gem[0];
    if(tot_money<gem[N-1]) return 0;

    if(store[(N-1)*NN + tot_money -1]>0) return store[(N-1)*NN + tot_money-1];

    std::vector<int> allPossibility;
    int money = tot_money;
    int number = 0;
    allPossibility.push_back(smartWay(tot_money,gem,N-1, store, NN)); //不買
    allPossibility.push_back(smartWay(tot_money-gem[N-1],gem,N, store, NN) + gem[N-1]); //買
    if(allPossibility[0]<allPossibility[1])
    {
	 store[(N-1)*NN + tot_money-1] = allPossibility[1];
    	 return allPossibility[1];
    }
    store[(N-1)*NN + tot_money -1] = allPossibility[0];
    return allPossibility[0];
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, W;
    std::cin >> N >> W;
    int temp;
    int gem[N];
    int store[N*W];
    for(int i=0;i<N;i++)
    {
	for(int j=0;j<W;j++)
	{
	    store[i*W+j] = -1;
	}
    }
    for(int i=0;i<N;i++)
    {
	std::cin >> gem[i];
    }

    sort(gem, N);

    int normal, smart;
    for(int tot_money=1;tot_money<=W;tot_money++)
    {
	int n_money = normalWay(tot_money, gem, N);
	int s_money = smartWay(tot_money, gem, N, store, W);
//	std::cout << "s_money: " << s_money << ", n_money: " << n_money << std::endl;
	std::cout << s_money-n_money << std::endl;
    }
//    std::cout << (double)clock() / CLOCKS_PER_SEC << "S";
}

////////////////////////////////////////////////////////////////////////
///   Reference: https://web.ntnu.edu.tw/~algo/KnapsackProblem.html  ///
///////////////////////////////////////////////////////////////////////
