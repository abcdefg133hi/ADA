#include <iostream>

int main(){
    int n;
    std::cin >> n;
    int array[n];
    for(int i=0;i<n;i++){
	std::cin >> array[i];
    }
    long sum_max = array[0];
    long sum = 0;
    int begin = 0;
    while(begin<n){
	for(int i=begin;i<n;i++){
	    sum += array[i];
	    if((sum < 0) && (sum_max>=sum)){
		begin = i;
		break;
	    }
	    if(sum_max < sum) sum_max = sum;
	}
	begin++;
	sum = 0;
    }
    std::cout << sum_max;
}
