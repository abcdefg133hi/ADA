#include <iostream>
#include <cmath>

int N_test;
void zero(int *array)
{
    for(int i=0;i<100000;i++)
    {
	array[i] = 0;
    }
}

long long mysteriousValue(const int *a, int N, int begin)
{
    if(N==1) return 0;

    long long left=mysteriousValue(a, (N+1)/2, begin);
    long long right = mysteriousValue(a, N/2, begin+(N+1)/2);
    int *left_number = new int[100000];
    int *right_number = new int[100000];
    int *left_temp = new int[100000];
    int *right_temp = new int[100000];
    zero(left_number);
    zero(right_number);
    zero(left_temp);
    zero(right_temp);

    long long tot(0);
    int center = (N-1)/2 + begin;
    int min = a[center];
    left_number[a[center]]++;
    left_temp[a[center]]++;
    int index = 0;
    bool min_direction = true; //left:true, right:false
    bool right_is_min = false;
    bool left_is_min = false;
    bool temp_min_dir = false;
    int temp_min = min;
    while(true)
    {
//	if(index>=0) index++;
	index++;
	if(center+index>=begin+N) break;
//	if(index>0){
	if(a[center+index]<min)
	{
	    temp_min = a[center+index];
	    right_is_min = true;
	    //min = a[center+index];
	    //zero(right_temp);
	    if(min_direction!=false) temp_min_dir = min_direction;
	    min_direction = false;
	}
	if(a[center+index]+temp_min<100000 && a[center+index]-temp_min>0)
	{
	    if(min_direction)
	    {
		tot += left_temp[a[center+index]+temp_min];
		tot += left_temp[a[center+index]-temp_min];
	    }
	    else
	    {
		tot += left_number[a[center+index]+temp_min];
		tot += left_number[a[center+index]-temp_min];
	    }
	}
	else if(a[center+index]+temp_min<100000)
	{
	    if(min_direction) tot += left_temp[a[center+index]+temp_min];
	    else tot += left_number[a[center+index]+temp_min];
	}
	else if(a[center+index]-temp_min > 0)
	{
	    if(min_direction) tot += left_temp[a[center+index]-temp_min];
	    else tot += left_number[a[center+index]-temp_min];
	}
	//}
	if(center-index<begin) break;
	if(temp_min_dir)
	{
	    min_direction = !min_direction;
	    temp_min_dir = false;
	}

        //if(index<0){
	//index*=-1;
	if(a[center-index]<min)
	{
	    min = a[center-index];
	    //zero(left_temp);
	    min_direction = true;
	}
	if(a[center-index]+min<100000 && a[center-index]-min>0)
	{
	    if(min_direction)
	    {
		tot += right_number[a[center-index]+min];
		tot += right_number[a[center-index]-min];
	    }
	    else
	    {
		tot += right_temp[a[center-index]+min];
		tot += right_temp[a[center-index]-min];
	    }
	}
	else if(a[center-index]+min<100000)
	{
	    if(min_direction) tot += right_number[a[center-index]+min];
	    else tot += right_temp[a[center-index]+min];
	}
	else if(a[center-index]-min > 0)
	{
	    if(min_direction) tot += right_number[a[center-index]-min];
	    else tot += right_temp[a[center-index]-min];
	}
	//index*=-1;
	//}
	if(right_is_min)
	{
	    zero(right_temp);
	    if(temp_min < min)
	    {
	    	min = temp_min;
		min_direction = false;
	    }
	}
	if(left_is_min)
	{
	    zero(left_temp);
	    if(temp_min < min)
	    {
	    	min = temp_min;
		min_direction = false;
	    }
	}
	if(a[center+index]+min==a[center-index]||a[center+index]-min==a[center-index]) tot++;
//	if(index>0)
//	{
	    right_number[a[center+index]]++;
	    right_temp[a[center+index]]++;
//	}
//	if(index<0)
//	{
	    left_number[a[center-index]]++;
	    left_temp[a[center-index]]++;
//	}
    }
    delete [] left_number;
    delete [] right_number;
    delete [] left_temp;
    delete [] right_temp;
    return tot+left+right;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    N_test = N;

    int a[N];
    for(int i=0;i<N;i++)
    {
	std::cin >> a[i];
    }

    long long value = mysteriousValue(a, N, 0);
//    int value = test(a,N);
    std::cout << value;
}
