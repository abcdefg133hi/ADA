#include <iostream>


int Hanoi(int n){
    if(n==1) return 1;
    if(n==2) return 3;
    return Hanoi(n-1)*2 + 1;
}

int main(){
    for(int i=1;i<=20;i++){
	std::cout << "For " << i << " disks, one should move " << Hanoi(i)
		<< " terms." << std::endl;
    }
}
