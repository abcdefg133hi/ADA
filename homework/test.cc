//This file is used for testing. Please don't use this file to save your important documents.
#include <iostream>
#include <vector>
#include <string>
using namespace std;
string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const int total_char = 62;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<vector<int> > quantity(2*total_char);
    int use[total_char];
    vector<char> result;
    string s;
    long long K;
    for(int i=0;i<62;i++)
    {
	 use[i] = 0;
    }
    cin >> s >> K;
    int N = s.length();
    bool if_use[N];
    for(int i=0;i<N;i++)
    {
	if_use[i] = false;
	int sum = 0;
	for(int code=total_char-1;code>=0;code--)
	{
	    if(s[i]==table[code])
	    {
		use[code]++;
		quantity[code].push_back(sum);
		quantity[total_char+code].push_back(i);
	    }
	    sum += use[code];
	}
    }
    int charth = 0;
    int number = 0;
    while(true)
    {
	if(charth>=total_char) break;
	if(!quantity[charth].empty())
	{
	    int idx = quantity[charth+total_char][number];
	    if_use[idx] = true;
	    K = K - quantity[charth][number];
	    result.push_back(table[charth]);
	}
	if(K<0)
	{
	    int idx = quantity[charth+total_char][number];
	    if_use[idx] = false;
	    K = K + quantity[charth][number];
	    result.pop_back();
	    break;
	}
	if(number+1>=quantity[charth].size())
	{
	    charth++;
	    number = 0;
	}
	else number++;
    }
    if(number>0) quantity[charth][0] = -number;
    for(int i=0;i<total_char;i++) use[i] = 0;
    while(K>0)
    {
	int charth_lower = charth;
	int use_which = -1;
	int use_hello = -1;
	for(int i=charth_lower;i<total_char;i++)
	{
	    if(!quantity[i].empty())
	    {
		int hello;
		if(quantity[i][0]>=0) hello = 0;
		else hello = -quantity[i][0];
		if(hello>=quantity[total_char+i].size()) continue;

		if(quantity[i][hello]-use[i]<=K)
		{
		    use_which = i;
		    use_hello = hello;
		    break;
		}
	    }
	}
	if(use_which==-1) break;
	int idx = quantity[total_char+use_which][use_hello];
	K = K - quantity[use_which][use_hello] + use[use_which];
	quantity[use_which][0] = -(use_hello+1);
	if_use[idx] = true;
	result.push_back(table[use_which]);
	for(int i=0;i<use_which;i++)
	{
	    use[i]++;
	}
    }
    for(int i=0;i<result.size();i++) cout << result[i];
    for(int i=0;i<N;i++)
    {
	if(!if_use[i]) cout << s[i];
    }
}
