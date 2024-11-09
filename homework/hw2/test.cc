#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;
vector<vector<int> > target(2);
vector<vector<int> > even(3);
vector<char> result;
int o=0;

void i_will_finish(long long &K, string s, int begin, int *array)
{
    o++;
    for(int i=0;i<even[0].size();i++)
    {
	int position = even[1][i];
	if(o<10) cout << position-K << endl;
	if((position-K)==begin)
	{
	    char temp = (char)even[0][i];
	    result.push_back(temp);
	    array[even[2][i]] = 400;
	    K = 0;
	    cout << "stop";
	    return;
	}
	if(even[1][i]==begin)
	{
	    char temp = (char)even[0][i];
	    result.push_back(temp);
	    array[even[2][i]] = 400;
	    i_will_finish(K, s, begin+1, array);
	    return;
	}
    }
}
int main()
{
    string s;
    long long K;
    cin >> s >> K;
    int N = s.length();
    int array[N];
    bool if_use[N];
    for(int i=0;i<N;i++)
    {
	array[i] = (int)s[i];
	if_use[i] = false;
	target[0].push_back(array[i]);
	target[1].push_back(i);
    }
    sort(target[0].begin(), target[0].end(), greater<int>() );
    int index(0);
    bool hello=false;
    while(true)
    {
	int value = target[1].back();
	int use = 0;
	for(int i=0;i<value;i++)
	{
	    if(if_use[i]) use++;
	}
	if(value==index)
	{
	    array[value] = 400;
	    result.push_back(s[value]);
	    if_use[value] = true;
	    target[0].pop_back();
	    if(index==0) hello =true;
	    index++;
	}
	else if(K-value+use>=0)
	{
	    array[value] = 400;
	    K = K - value + use;
	    result.push_back(s[value]);
	    if_use[value] = true;
	    target[0].pop_back();
	    index++;
	    cout << use << ", ";
	}
	else if(K>0)
	{
	    int i=0;
	    int j=0;
	    while(i<N)
	    {
		if(array[i]!=400)
		{
		    even[0].push_back(array[i]);
		    even[1].push_back(j);
		    even[2].push_back(i);
		    j++;
		}
		i++;
	    }
	    sort(even[0].begin(), even[0].end());
	    i_will_finish(K, s, 0, array);
	}
	if(K==0)
	{
	    for(int i=0;i<N;i++)
	    {
		if(array[i]!=400) result.push_back(s[i]);
	    }
	    break;
	}
    }
    /*
    for(int i=0;i<N;i++)
    {
	cout << array[i] << ", ";
    }
    cout << "\n";
*/
    for(int i=0;i<result.size();i++)
    {
	cout << result[i];
    }
}
