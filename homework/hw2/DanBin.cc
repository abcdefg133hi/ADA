#include <iostream>
#include <vector>

std::vector<long long> A, B;
std::vector<long long> idx;
void sort(std::vector<long long> &a, std::vector<long long> &b, int begin, int end)
{
    if(end==(begin+1)) return;
    sort(a, b, begin, begin+(end-begin+1)/2);
    sort(a, b, begin+(end-begin+1)/2, end);
    //std::cout << b.size();
    std::vector<int> temp_a, temp_b;
    int tot_idx(begin), left_idx(begin), right_idx(begin+(end-begin+1)/2);
    while(tot_idx < end)
    {
	if(right_idx>=end)
	{
	    for(int i=left_idx;i<begin+(end-begin+1)/2;i++)
	    {
		temp_a.push_back(a[i]);
	    	temp_b.push_back(b[i]);
	    }
	    break;
	}
	if(left_idx >= begin+(end-begin+1)/2)
	{
	    for(int i=right_idx;i<end;i++)
	    {
		//if(end-begin==4) std::cout << i << std::endl;
		temp_a.push_back(a[i]);
	    	temp_b.push_back(b[i]);
	    }
	    break;
	}
	if(b[right_idx]>b[left_idx])
	{
	    temp_a.push_back(a[right_idx]);
	    temp_b.push_back(b[right_idx]);
	    right_idx++;
	}
	else
	{
	    temp_a.push_back(a[left_idx]);
	    temp_b.push_back(b[left_idx]);
	    left_idx++;
	}
	tot_idx++;
    }
    int k(0);
    for(int i=begin;i<end;i++)
    {
	a[i] = temp_a[k];
	b[i] = temp_b[k];
	k++;
    }
}
void sort_inc(std::vector<long long> &a, std::vector<long long> &b, int begin, int end, std::vector<long long> &index)
{
    if(end==(begin+1)) return;
    sort_inc(a, b, begin, begin+(end-begin+1)/2, index);
    sort_inc(a, b, begin+(end-begin+1)/2, end, index);
    //std::cout << b.size();
    std::vector<long long> temp_a, temp_b, temp_idx;
    int tot_idx(begin), left_idx(begin), right_idx(begin+(end-begin+1)/2);
    while(tot_idx < end)
    {
	if(right_idx>=end)
	{
	    for(int i=left_idx;i<begin+(end-begin+1)/2;i++)
	    {
		temp_a.push_back(a[i]);
	    	temp_b.push_back(b[i]);
		temp_idx.push_back(index[i]);
	    }
	    break;
	}
	if(left_idx >= begin+(end-begin+1)/2)
	{
	    for(int i=right_idx;i<end;i++)
	    {
		//if(end-begin==4) std::cout << i << std::endl;
		temp_a.push_back(a[i]);
	    	temp_b.push_back(b[i]);
		temp_idx.push_back(index[i]);
	    }
	    break;
	}
	if(b[right_idx]*index[left_idx]<=b[left_idx]*index[right_idx])
//	if(b[right_idx]<b[left_idx])
	{
	    temp_a.push_back(a[right_idx]);
	    temp_b.push_back(b[right_idx]);
	    temp_idx.push_back(index[right_idx]);
	    right_idx++;
	}
	else
	{
	    temp_a.push_back(a[left_idx]);
	    temp_b.push_back(b[left_idx]);
	    temp_idx.push_back(index[left_idx]);
	    left_idx++;
	}
	tot_idx++;
    }
    int k(0);
    for(int i=begin;i<end;i++)
    {
	a[i] = temp_a[k];
	b[i] = temp_b[k];
	index[i] = temp_idx[k];
	k++;
    }
}

long long oneTime(std::vector<long long> &a, std::vector<long long> &b)
{
    int size = b.size();
    sort(a, b, 0, size);
    /*
    for(int i=0;i<4;i++)
    {
	std::cout << "(" << a[i] << ", " << b[i] << ")" << std::endl;
    }*/
    long long sum = a[0];
    long long maxTime = a[0]+b[0];
    for(int i=1;i<size;i++)
    {
	sum += a[i];
	if(maxTime < sum+b[i]) maxTime = sum+b[i];
    }
    return maxTime;
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    std::cin >> N;
    int m[N];
    std::vector<std::vector<long long> > a(N);
    std::vector<std::vector<long long> > b(N);
    for(int i=0;i<N;i++)
    {
	std::cin >> m[i];
	for(int j=0;j<m[i];j++)
	{
	    long long temp;
	    std::cin >> temp;
	    a[i].push_back(temp);
	    std::cin >> temp;
	    b[i].push_back(temp);
	}
    }
    for(int i=0;i<N;i++)
    {
	long long value = oneTime(a[i], b[i]);
	B.push_back(value);
	long long sum = 0;
	for(int j=0;j<a[i].size();j++) sum += a[i][j];
	A.push_back(sum);
	idx.push_back(a[i].size());
    }

    sort_inc(B, A, 0, N, idx);
    long long time = 0;
    long long result = (time+B[0])*idx[0];
    for(int i=1;i<N;i++)
    {
	time += A[i-1];
	result += (time+B[i])*idx[i];
    }
    std::cout << result;

    /*
    if(N==1)
    {
	long long value = oneTime(a[0], b[0]);
	std::cout << value;
    }
    else
    {
	std::cout << 0;
    }*/
    /*
    sort(a[0], b[0], 2, b[0].size());
    for(int i=0;i<b[0].size();i++)
    {
	std::cout << b[0][i] << std::endl;
    }*/
}
