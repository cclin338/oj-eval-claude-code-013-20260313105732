#include "../../src/map.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

int A = 325, B = 2336, Last = 233, Mod = 1000007;

int Rand(){
	return Last = (A * Last + B) % Mod;
}

void easy_test(){
	sjtu::map<int, int> Q;
	Q.clear();
	sjtu::map<int, int> :: iterator it;
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) std::swap(num[Rand() % 3000 + 1], num[Rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(Q.count(num[i])){
				it = Q.find(num[i]); Q.erase(it);
			}
			else std::cout << "fuck you!" << std::endl;
		}
		else{
			Q[num[i]] = num[i];
			left[num[i]]++;
		}
	}
	for(it = Q.begin(); it != Q.end(); ++it){ 
		std::cout << it -> first << " "  << it -> second << " ";
	}
	std::cout << std::endl;
}

int main(){
	srand(time(NULL));
	easy_test();
	std::cout << "Test passed!" << std::endl;
	return 0;
}
