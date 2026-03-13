#include "../../src/map.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

int Rand(){
	return (rand() << 16) + (rand() << 1) + rand();
}

int main() {
    sjtu::map<int, int> Q;
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	
	srand(1);
	for(int i = 1; i <= 6000; i++) {
	    int a = Rand() % 3000 + 1;
	    int b = Rand() % 3000 + 1;
	    int temp = num[a];
	    num[a] = num[b];
	    num[b] = temp;
	}
	
	for(int i = 1; i <= 3000; i++){
	    std::cout << "i=" << i << " num[i]=" << num[i] << " left[num[i]]=" << left[num[i]] << std::endl;
		if(left[num[i]]){
			if(Q.count(num[i])){
			    std::cout << "  Erasing " << num[i] << std::endl;
				auto it = Q.find(num[i]);
				Q.erase(it);
				std::cout << "  Erased, size=" << Q.size() << std::endl;
			}
			else std::cout << "ERROR: expected to find " << num[i] << std::endl;
		}
		else{
		    std::cout << "  Inserting " << num[i] << std::endl;
			Q[num[i]] = num[i];
			left[num[i]]++;
			std::cout << "  Inserted, size=" << Q.size() << std::endl;
		}
		
		if (i > 10) break;  // Only first 10 iterations for debugging
	}
    
    return 0;
}
