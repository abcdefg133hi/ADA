#include <iostream>

long MaxSubarray(int *array, int n){
    if(n==1) return array[0];

    int leftSize, rightSize;
    int left[(n+1)/2], right[n/2];
    if(n%2==1){
	//split array into left & right
	for(int idx=0;idx<(n-1)/2;idx++){
	    left[idx] = array[idx];
	    right[idx] = array[(n+1)/2 + idx];
	}
	left[(n-1)/2] = array[(n-1)/2];

	leftSize = (n+1)/2;
	rightSize = (n-1)/2;
    }
    else{
	//split array into left & right
	for(int idx=0;idx<n/2;idx++){
	    left[idx] = array[idx];
	    right[idx] = array[n/2+idx];
	}
	leftSize = n/2;
	rightSize = n/2;
    }

    /*
    std::cout << n << ": left: " << std::endl;
    for(int i=0;i<leftSize;i++){
	std::cout << left[i] << ", ";
    }
    std::cout << n << ": right: " << std::endl;
    for(int i=0;i<rightSize;i++){
	std::cout << right[i] << ", ";
    }
    */

    long leftMax, rightMax, centerMax;
    leftMax = MaxSubarray(left, leftSize);
    rightMax = MaxSubarray(right, rightSize);

    //deal with centerMax
    centerMax = left[leftSize-1];
    int left_idx = leftSize-2;
    int right_idx = 0;
    long sum = centerMax;
//    if(n==5) std::cout << "cMMM: " << centerMax << std::endl;
//    std::cout << "rs" << rightSize << std::endl;
    bool inside = true;
    while(true){
	while(inside){
	    sum += right[right_idx];
	    if(sum<centerMax){
		sum -= right[right_idx];
		inside = false;
		break;
	    }
	    centerMax = sum;
//	    std::cout << "left_idx " << left_idx << ", right_idx: " << right_idx << ", sum: " << sum << std::endl;
	    right_idx++;
	    if(right_idx>rightSize-1){
		inside = false;
		break;
	    }
	}
	if(left_idx<0) break;
	sum += left[left_idx];
	if(sum<centerMax) break;
	centerMax = sum;
//	std::cout << "left_idx " << left_idx << ", right_idx: " << right_idx << ", sum: " << sum << std::endl;
	left_idx--;
    }


    if(leftMax>=rightMax && leftMax>=centerMax) return leftMax;
    if(rightMax>=leftMax && rightMax>=centerMax) return rightMax;

    return centerMax;
}

int main(){

    int n;
    std::cin >> n;
    int array[n];
    for(int i=0;i<n;i++){
	std::cin >> array[i];
    }
    std::cout << MaxSubarray(array, n);
}
