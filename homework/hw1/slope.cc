#include <iostream>
#include <algorithm>

int l1, l2, r1, r2;
double l,r;
//int N;

void sort(long long *x, long long *y, int N)
{
    if(N==1) return;
    long long left[(N+1)/2], right[N/2];
    long long left_y[(N+1)/2], right_y[N/2];
    for(int i=0;i<N/2;i++)
    {
	left[i] = x[i];
	right[i] = x[(N+1)/2+i];
	left_y[i] = y[i];
	right_y[i] = y[(N+1)/2+i];
    }
    if(N%2==1){
    	 left[(N+1)/2-1] = x[(N+1)/2-1];
    	 left_y[(N+1)/2-1] = y[(N+1)/2-1];
    }

    sort(left, left_y, (N+1)/2);
    sort(right, right_y, N/2);

    int left_idx(0), right_idx(0), total_idx(0);
    while(total_idx<N)
    {
	if(left_idx>=(N+1)/2)
	{
	    for(int i=right_idx;i<N/2;i++)
	    {
		x[(N+1)/2+i] = right[i];
		y[(N+1)/2+i] = right_y[i];
	    }
	    break;
	}

	if(right_idx>=N/2)
	{
	    for(int i=left_idx;i<(N+1)/2;i++)
	    {
		x[N/2+i] = left[i];
		y[N/2+i] = left_y[i];
	    }
	    break;
	}

	if(left[left_idx]<right[right_idx])
	{
	    x[total_idx] = left[left_idx];
	    y[total_idx] = left_y[left_idx];
	    left_idx++;
	}
	else if(left[left_idx]==right[right_idx])
	{
	    if(left_y[left_idx]<right_y[right_idx])
	    {
		x[total_idx] = left[left_idx];
		y[total_idx] = left_y[left_idx];
		left_idx++;
	    }
	    else
	    {
		x[total_idx] = right[right_idx];
		y[total_idx] = right_y[right_idx];
		right_idx++;
	    }
	}
	else
	{
	    x[total_idx] = right[right_idx];
	    y[total_idx] = right_y[right_idx];
	    right_idx++;
	}
	total_idx++;
    }
}


long long inversion_right(long long *gem, int N)
{
    if(N==1) return 0;
    long long left[(N+1)/2], right[N/2];
    for(int i=0;i<N/2;i++)
    {
	left[i] = gem[i];
	right[i] = gem[(N+1)/2+i];
    }
    if(N%2==1) left[(N+1)/2-1] = gem[(N+1)/2-1];

    long long left_inv = inversion_right(left, (N+1)/2);
    long long right_inv = inversion_right(right, N/2);

    int left_idx(0), right_idx(0), total_idx(0);
    long long cen_inv = 0;
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

	if(left[left_idx]<right[right_idx])
	{
	    gem[total_idx] = left[left_idx];
	    left_idx++;
	}
	else
	{
	    gem[total_idx] = right[right_idx];
	    cen_inv+=(N+1)/2-left_idx;
	    right_idx++;
	}
	total_idx++;
    }
    return left_inv + right_inv + cen_inv;
}
long long inversion_left(long long *gem, int N)
{
    if(N==1) return 0;
    long long left[(N+1)/2], right[N/2];
    for(int i=0;i<N/2;i++)
    {
	left[i] = gem[i];
	right[i] = gem[(N+1)/2+i];
    }
    if(N%2==1) left[(N+1)/2-1] = gem[(N+1)/2-1];

    long long left_inv = inversion_left(left, (N+1)/2);
    long long right_inv = inversion_left(right, N/2);

    int left_idx(0), right_idx(0), total_idx(0);
    long long cen_inv = 0;
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

	if(left[left_idx]<=right[right_idx])
	{
	    gem[total_idx] = left[left_idx];
	    left_idx++;
	}
	else
	{
	    gem[total_idx] = right[right_idx];
	    cen_inv+=(N+1)/2-left_idx;
	    right_idx++;
	}
	total_idx++;
    }
    return left_inv + right_inv + cen_inv;
}

long long number_not_fly(long long *x, long long *y, int N)
{
    long long Y[N];
    for(int i=0;i<N;i++)
    {
	Y[i] = r2*y[i] - r1*x[i];
    }
    long long right = inversion_right(Y, N);
    for(int i=0;i<N;i++)
    {
	Y[i] = l2*y[i] - l1*x[i];
    }
    long long left = inversion_left(Y, N);

    return right - left;
}


bool if_can_fly(int x1, int x2, int y1, int y2)
{
    if(x1==x2) return true;
    float slope = 1.*(y2-y1)/(x2-x1);
    if(slope<l || slope>r) return true;
    return false;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::cin >> l1 >> l2 >> r1 >> r2;

    long long x[N];
    long long y[N];
    for(int i=0;i<N;i++)
    {
	std::cin >> x[i] >> y[i];
    }

    long long result = 0;

/*
    l = l1/l2*1.;
    r = r1/r2*1.;
    if(N<=3000)
    {
	for(int i=0;i<N;i++)
	{
	    for(int j=(i+1);j<N;j++)
	    {
		if(if_can_fly(x[i], x[j], y[i], y[j])) continue;
		result++;
	    }
	}
	std::cout << result;
	return 0;
    }*/

    sort(x, y, N);
    long long y_prime[N];
    for(int i=0;i<N;i++) y_prime[i] = y[i];
    //result = inversion(y_prime, N);
    result = number_not_fly(x, y_prime,N);

/*
    for(int i=0;i<N;i++)
    {
	std::cout << "( " << x[i] << ", "  << y_prime[i] << " )" << std::endl;
    }*/

    std::cout << result;
}
