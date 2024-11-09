#include <iostream>
#include <string>

int minimum(int a, int b, int c)
{
    if(a<=b)
    {
	if(a<=c) return a;
    }
    else if(b<=c)
    {
	return b;
    }
    return c;

}


int minimum_cost(std::string X, std::string Y, int x_length, int y_length)
{
    if(x_length==0) return y_length;
    if(y_length==0) return x_length;

    int dynamic[x_length+1][y_length+1];
    for(int i=0;i<=x_length;i++)
    {
	for(int j=0;j<=y_length;j++)
	{
	    dynamic[i][j] = 0;
	}
    }

    for(int i=0;i<=x_length;i++)
    {
	for(int j=0;j<=y_length;j++)
	{
	    if(i==0) dynamic[i][j] = j;
	    else if(j==0) dynamic[i][j] = i;
	    else if(X[i-1]==Y[j-1])
	    {
	    	dynamic[i][j] = dynamic[i-1][j-1];
	    }
	    else
	    {
		dynamic[i][j] = minimum(dynamic[i][j-1], dynamic[i-1][j], dynamic[i-1][j-1]) + 1;
	    }
	}
    }
    return dynamic[x_length][y_length];

}
int main()
{
    std::string X, Y;
    std::cin >> X >> Y;

    int x_length(0), y_length(0);
    while(X[x_length]!='\0')
    {
	x_length++;
    }
    while(Y[y_length]!='\0')
    {
	y_length++;
    }

    int result = minimum_cost(X, Y, x_length, y_length);
    std::cout << result;
}
