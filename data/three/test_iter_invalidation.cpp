#include "../../src/map.hpp"
#include <iostream>

int main() {
    sjtu::map<int, int> Q;
    
    // Insert elements
    for (int i = 1; i <= 10; i++) {
        Q[i] = i;
    }
    
    std::cout << "Initial map:" << std::endl;
    for (auto it = Q.begin(); it != Q.end(); ++it) {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;
    
    // Test: Get an iterator to end, insert more elements, then try to decrement from end
    auto end_it = Q.end();
    
    Q[15] = 15;
    Q[20] = 20;
    
    std::cout << "After insertions:" << std::endl;
    for (auto it = Q.begin(); it != Q.end(); ++it) {
        std::cout << it->first << " ";
    }
    std::cout << std::endl;
    
    // Now try to decrement from the old end iterator
    std::cout << "Decrementing from end:" << std::endl;
    auto it = end_it;
    --it;
    std::cout << "Last element: " << it->first << std::endl;
    
    return 0;
}
