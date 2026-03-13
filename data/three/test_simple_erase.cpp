#include "../../src/map.hpp"
#include <iostream>

int main() {
    sjtu::map<int, int> Q;
    
    // Insert and erase in a pattern similar to easy_test
    Q[1] = 1;
    Q[2] = 2;
    std::cout << "Inserted 1, 2" << std::endl;
    
    auto it = Q.find(1);
    Q.erase(it);
    std::cout << "Erased 1" << std::endl;
    
    // Try to insert 1 again
    Q[1] = 1;
    std::cout << "Inserted 1 again" << std::endl;
    
    // Erase 1 again
    it = Q.find(1);
    Q.erase(it);
    std::cout << "Erased 1 again" << std::endl;
    
    // Print remaining
    std::cout << "Remaining: ";
    for (auto iter = Q.begin(); iter != Q.end(); ++iter) {
        std::cout << iter->first << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
