#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> steps;
void photo(int N, int *array)
{
    if(N==1)
    {
	steps.push_back("PHOTO");
	return;
    }
    int top[(N+1)/2], bottom[N/2];
    int topSize, bottomSize;
    for(int i=0;i<N/2;i++)
    {
	top[i] = array[i];
	bottom[i] = array[(N+1)/2+i];
    }
    if(N%2==1){
    	 top[(N-1)/2] = array[(N-1)/2];
    }
    topSize = (N+1)/2;

    bottomSize = N/2;

    //deal with top
    photo(topSize, top);

    //change the position of top and bottom
    for(int i=0;i<N;i++) steps.push_back("POP");
    for(int i=0;i<topSize;i++) steps.push_back("PLACE "+std::to_string(top[i]));
    for(int i=0;i<bottomSize;i++) steps.push_back("PLACE "+std::to_string(bottom[bottomSize-1-i]));

    //deal with bottom
    photo(bottomSize, bottom);
}
int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    std::cin >> N;
    int array[N];
    for(int i=0;i<N;i++){
	array[i] = i+1;
	steps.push_back("PLACE "+std::to_string(N-i));
    }
    photo(N, array);
    std::cout << steps.size() << std::endl;
    for(int i=0;i<steps.size();i++)
    {
	std::cout << steps[i] << std::endl;
    }
}
