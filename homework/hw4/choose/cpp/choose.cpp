#include "choose.h"
#include <algorithm>
#include <vector>
//#include <iostream>

/*
Feel free to use global variables.
However, if you want to write your code more "correctly",
you can search for the keyword "anonymous namespace", a helpful tool in C++.
*/


typedef std::pair<int, int> pp; //(time, id)
int time_1(0);
int time_2(0);
std::vector<int> tasking;
// this is an example usage
void schedule(int N) {
    int endtime[N+1];
    tasking.resize(N);
    for(int i=0;i<N;i++) tasking[i] = i+1;
    for(int j=0;j<N;j++)
    {
	for(int i=0;i<N-1;i++)
	{
	    int compare_res = compare_task(tasking[i],tasking[i+1]);
	    if(compare_res<=0)
	    {
		int temp = tasking[i];
		tasking[i] = tasking[i+1];
		tasking[i+1] = temp;
	    }
	}
    }
    for(int i=0;i<N;i++)
    {
	if(time_1<time_2)
	{
	    endtime[tasking[i]] = assign_task(1, tasking[i]);
	    time_1 = endtime[tasking[i]];
	}
	else
	{
	    endtime[tasking[i]] = assign_task(2, tasking[i]);
	    time_2 = endtime[tasking[i]];
	}
    }
}


