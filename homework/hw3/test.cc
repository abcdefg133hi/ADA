#include <iostream>
#include <algorithm>
#include <vector>

int take(0);
int record(0);
std::vector<std::pair<long long, int> > rod;
std::vector<long long > p_sum;
std::vector<int > takeaway;
//first: wieght, second: index
//


void print_rod()
{
    std::cout << "----------" << "\n";
    for(int i=0;i<rod.size();i++)
	{
	    std::cout << rod[i].first << ", ";
	}
    std::cout << "\n";
}
void print_take()
{
    std::cout << "----------" << "\n";
    for(int i=0;i<takeaway.size();i++)
	{
	    std::cout << takeaway[i] << ", ";
	}
    std::cout << "\n";
}
void print_p()
{
    std::cout << "----------" << "\n";
    for(int i=0;i<p_sum.size();i++)
	{
	    std::cout << p_sum[i] << ", ";
	}
    std::cout << "\n";
}
bool w_compare(std::pair<long long, int> a, std::pair<long long, int> b)
{
    return a.first < b.first;
}

bool index_compare(std::pair<long long, int> a, std::pair<long long, int> b)
{
    return a.second < b.second;
}
long long to_command(std::string s)
{
    if(s=="PUT") return 0;
    if(s=="TAKE") return 1;
    if(s=="CC") return 2;
    if(s=="DD") return 3;
}

void Take()
{
//    take++;
    int size = rod.size();
    long long w = rod[size-1].first;
    rod.pop_back();
    //takeaway.push_back(std::make_pair(w,record-1));
    p_sum.pop_back();
    std::cout << w << "\n";
}

void Put(long long weight)
{
    int size = p_sum.size();
    if(size==0) p_sum.push_back(weight);
    else p_sum.push_back(weight+p_sum[size-1]);
    //std::cout << "Put weight: " << weight << "\n";
    rod.push_back(std::make_pair(weight, size));
    record++;
}

void CC(long long x, long long k)
{
    std::vector<std::pair<long long, int> > temp_rod;
    std::vector<long long> temp_p;
    int size = rod.size();
    long long rew = 0;
    for(int i=0;i<x;i++)
    {
	long long w = rod.back().first;
	int idx = rod.back().second;
	rod.pop_back();
	temp_rod.push_back(std::make_pair(w, idx));
    }
    int oldidx;
    if(!rod.empty()) oldidx = rod.back().second;
    else oldidx = -1;
    int count = x/k+1;
    if(x%k==0) count -= 1;
    long long sum(0);
    std::sort(temp_rod.begin(), temp_rod.end(), w_compare);
    for(int i=0;i<count;i++)
    {
	long long alpha = temp_rod.back().first;
	int idx = temp_rod.back().second;
	sum += alpha;
	takeaway.push_back(idx);
	temp_rod.pop_back();
    }
    std::sort(temp_rod.begin(), temp_rod.end(), index_compare);
    std::sort(takeaway.begin(), takeaway.end());
    int newidx = size-x;
    if(temp_rod.size()>0 && oldidx >=0)
    {
	int idx = temp_rod[0].second;
	if(idx-1>oldidx) rew = (p_sum[idx-1] - p_sum[oldidx]);
	p_sum[idx] -= rew;
    }
    if(temp_rod.size()>0) {
    	oldidx = temp_rod[0].second;
	temp_rod[0].second = newidx;
	rod.push_back(temp_rod[0]);
	newidx++;
    }
    for(int i=1;i<temp_rod.size();i++)
    {
	int idx = temp_rod[i].second;
	if(idx-1>oldidx) rew = (p_sum[idx-1] - p_sum[oldidx]);
	p_sum[idx] -= rew;
	temp_rod[i].second = newidx;
	newidx++;
	oldidx = idx;
	rod.push_back(temp_rod[i]);
    }
    temp_rod.clear();
    for(int i=0;i<x;i++)
    {
	if(size-1-i == takeaway.back() && takeaway.size()>0)
	{
	    takeaway.pop_back();
	    p_sum.pop_back();
	}
	else
	{
	    temp_p.push_back(p_sum.back());
	    p_sum.pop_back();
	}
    }

    //print_p();
    int ss = temp_p.size();
    for(int i=0;i<ss;i++)
    {
	p_sum.push_back(temp_p.back());
	temp_p.pop_back();
    }
    //print_rod();
    takeaway.clear();
    std::cout << sum << "\n";
}

void DD(long long x)
{
    long long result = p_sum.back() - p_sum[p_sum.size()-x] + rod[p_sum.size()-x].first;
    std::cout << result << "\n";
}
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int M;
    std::cin >> M;
    std::string temp_command;
    std::vector<std::vector<long long> > command(M);
    for(int i=0;i<M;i++)
    {
	std::cin >> temp_command;
	command[i].push_back(to_command(temp_command));
	switch(command[i][0])
	{
	    case 0:
		long long w;
		std::cin >> w;
		command[i].push_back(w);
		break;
	    case 1:
		break;
	    case 2:
		long long x, k;
		std::cin >> x >> k;
		command[i].push_back(x);
		command[i].push_back(k);
		break;
	    case 3:
		long long s;
		std::cin >> s;
		command[i].push_back(s);
		break;
	}
    }
    for(int i=0;i<M;i++)
    {
	long long dir = command[i][0];
	switch(dir)
	{
	    case 0:{
		long long w = command[i][1];
		Put(w);
		break;}
	    case 1:{
		Take();
		break;}
	    case 2:{
		long long x = command[i][1];
		long long k = command[i][2];
		CC(x, k);
		break;}
	    case 3:{
		long long s = command[i][1];
		DD(s);
		break;}
	}
    }
}
