#include <iostream>
#include <cstdlib>
#include <algorithm>

int Rand(){
	return (rand() << 16) + (rand() << 1) + rand();
}

int main() {
	int num[3001];
	for(int i = 1; i <= 2000; i++) num[i] = i;
	for(int i = 2001; i <= 3000; i++) num[i] = i - 2000;
	
	srand(1);
	for(int i = 1; i <= 6000; i++) {
	    int a = Rand() % 3000 + 1;
	    int b = Rand() % 3000 + 1;
	    std::cout << "swap indices: " << a << ", " << b << std::endl;
	    if (i > 5) break;
	}
    
    return 0;
}
