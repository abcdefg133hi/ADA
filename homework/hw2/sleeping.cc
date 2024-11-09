#include <iostream>

long long maxValue(long long a, long long b, long long c)
{
    if(a>b)
    {
	if(a>c) return a;
    }
    if(b>c) return b;
    return c;
}
long long maximumSubarray(int *array, int begin, int N, long long *ms, int ms_N)
{
    if(N==1)
    {
	ms[begin*ms_N + begin] = array[begin];
    	return array[begin];
    }
    long long left = maximumSubarray(array, begin, (N+1)/2, ms, ms_N);
    long long right = maximumSubarray(array, begin+(N+1)/2, N/2, ms, ms_N);
    long long center = begin + (N+1)/2-1;
    int index(0);
    int left_sum = array[center];
    int right_sum = array[center+1];
    int sum = 0;
    int rec_i(center), rec_j(center+1);
    for(int i=center;i>=begin;i--)
    {
	sum += array[i];
	if(sum > left_sum){
	    left_sum = sum;
	}
    }
    sum = 0;
    for(int i=center+1;i<begin+N;i++)
    {
	sum += array[i];
	if(sum > right_sum)
	{
	    right_sum = sum;
	}
    }
    long long result =  maxValue(left, right, left_sum+right_sum);
    ms[begin*ms_N + begin + (N-1)] = result;
    return result;
}
long long maxSubArray(int *array, int begin, int N)
{
    int res = array[begin];
    int current = array[begin];
    for(int i=begin+1;i<begin+N;i++)
    {
	current += array[i];
	if(current < 0 || array[i] > current) current = array[i];
	if(res < current) res = current;
    }
    return res;
}
long long valueMax(int *array,int j, long long *oldValue, int num)
{
    long long res = array[j-1];
    long long current = array[j-1];
    long long min = oldValue[j-1] + res;
    for(int k=2;k<j;k++)
    {
	if((j-k)<num) break;
	current += array[j-k];
	if(current < 0 || array[j-k] > current) current = array[j-k];
	if(res < current) res = current;
	if(min > oldValue[j-k] + k*res) min = oldValue[j-k] + k*(res);
	    /*
	    for(int k=2;k<j;k++)
	    {
		if((j-k)<i-1) break;
		//long long value;
		//if(ms[(j-k)*N +k-1]!=0) value = ms[(j-k)*N + k-1];
		//else value = maximumSubarray(array, j-k, k, ms, N);
		//long long value = maximumSubarray(array, j-k, k);
		long long value = maxSubArray(array, j-k, k);
		if(min>dynamic[i-1][j-k] + k*value) min = dynamic[i-1][j-k] + k*value;
	    }
	    dynamic[i][j] = valueMax(array, j, dynamic[i-1], i-1);
	    */
    }
    return min;
}


long long sleep(int *array, int N, int K)
{
    long long dynamic[K+1][N+1];
    long long ms[N][N];
    for(int i=0;i<N;i++)
    {
	for(int j=0;j<N;j++)
	{
	    ms[i][j] = 0;
	}
    }
    for(int i=0;i<=K;i++)
    {
	for(int j=i;j<=N;j++)
	{
	    if(i==0)
	    {
		dynamic[i][j] = 0;
		continue;
	    }
	    if(i==1)
	    {
		//long long arr = maximumSubarray(array, 0, j, ms, N);
		long long arr = maxSubArray(array, 0, j);
		dynamic[i][j] = arr*j;
		continue;
	    }
	    //long long min = dynamic[i-1][j-1] + array[j-1];
	    /*
	    for(int k=2;k<j;k++)
	    {
		if((j-k)<i-1) break;
		//long long value;
		//if(ms[(j-k)*N +k-1]!=0) value = ms[(j-k)*N + k-1];
		//else value = maximumSubarray(array, j-k, k, ms, N);
		//long long value = maximumSubarray(array, j-k, k);
		long long value = maxSubArray(array, j-k, k);
		if(min>dynamic[i-1][j-k] + k*value) min = dynamic[i-1][j-k] + k*value;
	    }
	    */
	    dynamic[i][j] = valueMax(array, j, dynamic[i-1], i-1);
	}
    }
    return dynamic[K][N];
}
/*

long long two_min(long long a, long long b)
{
    if(a>b) return b;
    return a;
}
long long temp(int *array, int N, int K)
{
    long long dynamic[1002][1002];
    for(int i=0;i<1002;i++)
    {
	for(int j=0;j<1002;j++)
	{
	    dynamic[i][j] = -1E13;
	}
    }
    return sleeping(array, N, K, dynamic);
}
long long sleeping(int *array, int N, int K, long long dynamic[1002][1002])
{
    if(K==1)
    {
	dynamic[K][N] = maximumSubarray(array, 0, N)*N;
    	return dynamic[K][N];
    }
    long long min;
    if(dynamic[K-1][N-1]>-5E12) min = dynamic[K-1][N-1] + array[N-1];
    else min = sleeping(array, N-1, K-1, dynamic[1002][1002]) + array[N-1];
    for(int k=2;k<N;k++)
    {
	if(k>N-K+1) break;
	long long value = maximumSubarray(array, N-k, k);
	if(dynamic[K-1][N-k]>-5E12) min = two_min(dynamic[K-1][N-k] + k*value, min);
	else
	{
	    min = two_min(min, sleeping(array, N-k, K-1, dynamic[1002][1002]) + k*value);
	}
    }
    dynamic[K][N] = min;
    return dynamic[K][N];
}
*/

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    int K;
    std::cin >> N >> K;
    int a[N];
    for(int i=0;i<N;i++) std::cin >> a[i];
//    zero();
    std::cout << sleep(a, N, K);
    return 0;
}
