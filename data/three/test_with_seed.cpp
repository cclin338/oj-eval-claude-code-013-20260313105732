#include<iostream>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include "../../src/map.hpp"

using namespace std;

int Rand(){
	return (rand() << 16) + (rand() << 1) + rand();
}

void easy_test(){
	sjtu::map<int, int> Q;
	Q.clear();
	sjtu::map<int, int> :: iterator it;
	int num[3001], left[3001];
	memset(left, 0, sizeof(left));
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	for(int i = 1; i <= 6000; i++) swap(num[Rand() % 3000 + 1], num[Rand() % 3000 + 1]);
	for(int i = 1; i <= 3000; i++){
		if(left[num[i]]){
			if(Q.count(num[i])){
				it = Q.find(num[i]); Q.erase(it);
			}
			else cout << "fuck you!" << endl;
		}
		else{
			Q[num[i]] = num[i];
			left[num[i]]++;
		}
	}
	for(it = Q.begin(); it != Q.end(); ++it){ 
		cout << it -> first << " "  << it -> second << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[]){
    int seed = time(NULL);
    if (argc > 1) {
        seed = atoi(argv[1]);
    }
    cout << "Using seed: " << seed << endl;
	srand(seed);
	easy_test();
	cout << "Test passed!" << endl;
	return 0;
}
