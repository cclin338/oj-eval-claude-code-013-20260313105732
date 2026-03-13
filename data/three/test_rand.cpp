#include <iostream>
#include <cstdlib>

int Rand(){
	return (rand() << 16) + (rand() << 1) + rand();
}

int main() {
    srand(1);
    for (int i = 0; i < 10; i++) {
        int r = Rand();
        std::cout << "Rand() = " << r << " mod 3000+1 = " << (r % 3000 + 1) << std::endl;
    }
    return 0;
}
